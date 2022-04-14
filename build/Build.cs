using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Reflection;
using Aimp.DotNet.Build;
using Nuke.Common;
using Nuke.Common.CI.TeamCity;
using Nuke.Common.Execution;
using Nuke.Common.Git;
using Nuke.Common.IO;
using Nuke.Common.ProjectModel;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.DotNet;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Common.Tools.SonarScanner;
using Nuke.Common.Utilities;
using Nuke.Common.Utilities.Collections;
//using Nuke.PvsStudio;
using Serilog;
using static Nuke.Common.IO.FileSystemTasks;
using static Nuke.Common.IO.PathConstruction;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;

[CheckBuildProjectConfigurations]
partial class Build : NukeBuild
{
    public static int Main() => Execute<Build>(x => x.PrepareIntegrationTests);

    [Parameter("Configuration to build - Default is 'Debug' (local) or 'Release' (server)")]
    readonly Configuration Configuration = IsLocalBuild ? Configuration.Debug : Configuration.Release;

    [Solution] readonly Solution Solution;
    [GitRepository] readonly GitRepository GitRepository;
    [GitVersion(NoFetch = true, UpdateAssemblyInfo = false)] readonly GitVersion GitVersion;

    #region Parameters

    [Parameter] readonly string SonarUrl;
    [Parameter] readonly string SonarUser;
    [Parameter] readonly string SonarPassword;
    [Parameter] readonly string SonarProjectKey;
    [Parameter] readonly string SonarProjectName;

    [Parameter] readonly string NugetSource;
    [Parameter] readonly string NugetApiKey;

    [Parameter] readonly string RequestSourceBranch;
    [Parameter] readonly string RequestTargetBranch;
    [Parameter] readonly string RequestId;

    [Parameter]
    readonly string MsBuildPath =
        @"c:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MsBuild.exe";

    #endregion

    bool IsTeamCity => TeamCity.Instance != null;

    AbsolutePath SourceDirectory => RootDirectory / "src";
    AbsolutePath TestsDirectory => RootDirectory / "tests";
    AbsolutePath OutputDirectory => RootDirectory / "output";

    AbsolutePath PvsReportPath => OutputDirectory / "aimpDotNet.plog";

    readonly string MasterBranch = "master";
    readonly string DevelopBranch = "develop";
    readonly string ReleaseBranchPrefix = "release";
    readonly string HotfixBranchPrefix = "hotfix";
    string _version = "1.0.0.0";

    string ParameterOutputPattern = "Parameter {parameter}: {value}";

    Target PrintBuildParameters => _ => _
        .Executes(() =>
        {
            PrintParameters("Sonar");
            PrintParameters("Nuget");
            PrintParameters("Request");
            PrintParameters("IntegrationTest");
        });

    Target Clean => _ => _
        .Before(Restore)
        .Executes(() =>
        {
            SourceDirectory.GlobDirectories("**/bin", "**/obj").ForEach(DeleteDirectory);
            EnsureCleanDirectory(OutputDirectory);
        });

    Target Restore => _ => _
        .Executes(() =>
        {
            NuGetTasks.NuGetRestore(c => c.SetTargetPath(Solution));
            MSBuild(s => s
                .SetProcessToolPath(MsBuildPath)
                .SetTargetPath(Solution)
                .SetTargets("Restore"));
        });

    Target Version => _ => _
        .Executes(() =>
        {
            _version = GitRepository.Branch.StartsWith(ReleaseBranchPrefix)
                ? GitRepository.Branch.Split("/")[1]
                : GitVersion.AssemblySemVer;

            Serilog.Log.Information("Version: {_version}", _version);
            var assemblyInfo = SourceDirectory / "AssemblyInfo.cs";
            if (File.Exists(assemblyInfo))
            {
                Serilog.Log.Information("Update version for '{assemblyInfo}'", assemblyInfo);
                var fileContent = File.ReadAllText(assemblyInfo);
                fileContent = fileContent.Replace("1.0.0.0", _version);
                File.WriteAllText(assemblyInfo, fileContent);
            }

            var rcFile = SourceDirectory / "aimp_dotnet" / "aimp_dotnet.rc";
            if (File.Exists(rcFile))
            {
                Serilog.Log.Information("Update version for '{rcFile}'", rcFile);
                Serilog.Log.Information("Assembly version: {AssemblySemVer}", GitVersion.AssemblySemVer);
                var fileContent = File.ReadAllText(rcFile);
                fileContent = fileContent.Replace("1,0,0,1", _version.Replace(".", ",")).Replace("1.0.0.1", _version);
                File.WriteAllText(rcFile, fileContent);
            }

            if (TeamCity.Instance != null)
            {
                TeamCity.Instance.SetBuildNumber(_version);
            }
        });

    Target Compile => _ => _
        .DependsOn(PrintBuildParameters, Restore, Version)
        .Executes(() =>
        {
            MSBuild(s => s
                .SetProcessToolPath(MsBuildPath)
                .SetTargetPath(Solution)
                .SetTargets("Rebuild")
                .SetConfiguration(Configuration)
                .SetAssemblyVersion(_version)
                .SetFileVersion(_version)
                .SetInformationalVersion($"{_version}-{GitRepository.Commit}")
                .SetMaxCpuCount(Environment.ProcessorCount)
                .SetNodeReuse(IsLocalBuild));
        });

    Target SonarQube => _ => _
        .Requires(() => SonarUrl, () => SonarUser, () => SonarProjectKey, () => SonarProjectName)
        .DependsOn(Restore)
        .Executes(() =>
            {
                var framework = "net5.0";
                var configuration = new SonarBeginSettings()
                    .SetProjectKey(SonarProjectKey)
                    .SetIssueTrackerUrl(SonarUrl)
                    .SetServer(SonarUrl)
                    .SetVersion(_version)
                    //.SetHomepage(SonarUrl)
                    .SetLogin(SonarUser)
                    .SetPassword(SonarPassword)
                    .SetName(SonarProjectName)
                    //.SetWorkingDirectory(SourceDirectory)
                    .SetBranchName(GitRepository.Branch)
                    .SetFramework(framework)
                    .EnableVerbose();

                if (File.Exists(PvsReportPath))
                {
                    configuration = configuration.SetPvsStudioReportPath(PvsReportPath);
                }

                if (GitRepository.Branch != null && !GitRepository.Branch.Contains(ReleaseBranchPrefix))
                {
                    configuration = configuration.SetVersion(GitVersion.SemVer);
                }

                configuration = configuration.SetProjectBaseDir(SourceDirectory);

                if (!string.IsNullOrWhiteSpace(RequestSourceBranch) && !string.IsNullOrWhiteSpace(RequestTargetBranch))
                {
                    configuration = configuration
                        .SetPullRequestBase(RequestSourceBranch)
                        .SetPullRequestBranch(RequestTargetBranch)
                        .SetPullRequestKey(RequestId);
                }

                var path = ToolPathResolver.GetPackageExecutable(
                    packageId: "dotnet-sonarscanner",
                    packageExecutable: "SonarScanner.MSBuild.dll",
                    framework: framework);

                configuration = configuration.SetProcessToolPath(path);

                var arguments = $"{path} {configuration.GetProcessArguments().RenderForExecution()}";

                DotNetTasks.DotNet(arguments);
            }, () =>
            {
                MSBuild(c => c
                    .SetConfiguration(Configuration)
                    .SetProcessToolPath(MsBuildPath)
                    .SetTargets("Rebuild")
                    .SetSolutionFile(Solution)
                    .EnableNodeReuse());
            },
            () =>
            {
                var framework = "net5.0";
                var path = ToolPathResolver.GetPackageExecutable(
                    packageId: "dotnet-sonarscanner",
                    packageExecutable: "SonarScanner.MSBuild.dll",
                    framework: framework);

                var configuration = new SonarScannerEndSettings()
                    .SetLogin(SonarUser)
                    .SetPassword(SonarPassword)
                    .SetFramework(framework)
                    .EnableProcessLogOutput();

                var arguments = $"{path} {configuration.GetProcessArguments().RenderForExecution()}";

                DotNetTasks.DotNet(arguments);
            });

    Target PvsStudio => _ => _
        .Executes(() =>
        {
            //PvsStudioTasks.PvsStudioRun(c => c
            //    .SetConfiguration(Configuration)
            //    .SetTarget(Solution)
            //    .SetOutput(PvsReportPath));
        });

    Target Pack => _ => _
        .DependsOn(Version)
        .Executes(() =>
        {
            Serilog.Log.Information("Start build Nuget packages");

            var nugetFolder = RootDirectory / "Nuget";

            var config = new NuGetPackSettings()
                .SetBasePath(RootDirectory)
                .SetConfiguration(Configuration)
                .SetVersion(_version)
                .SetOutputDirectory(OutputDirectory);

            if (GitRepository.Branch != null && !GitRepository.Branch.Contains(ReleaseBranchPrefix))
            {
                config = config.SetSuffix("preview");
            }

            if (Configuration == Configuration.Debug)
            {
                config = config.SetSuffix("debug");
            }

            NuGetTasks.NuGetPack(config
                .SetTargetPath(nugetFolder / "AimpSDK.nuspec"));
        });

    Target Publish => _ => _
        .Requires(() => Configuration.Equals(Configuration.Release))
        .Requires(() => NugetApiKey)
        .Executes(() =>
        {
            PrintParameters("Nuget");

            Serilog.Log.Information("Deploying Nuget packages");
            var packages = GlobFiles(OutputDirectory, "*.nupkg")
                .Where(c => !c.EndsWith("symbols.nupkg")).ToList();

            Assert.NotEmpty(packages);

            packages
                .ForEach(c => NuGetTasks.NuGetPush(s => s
                    .SetTargetPath(c)
                    .SetApiKey(NugetApiKey)
                    .SetSource(NugetSource)));
        });

    Target Artifacts => _ => _
        .Executes(() =>
        {
            List<string> plugins = new List<string>();
            EnsureCleanDirectory(OutputDirectory / "Artifacts");
            Directory.CreateDirectory(OutputDirectory / "Artifacts");

            Serilog.Log.Information("Copy plugins to artifacts folder");

            var directories = GlobDirectories(SourceDirectory / "Plugins", $"**/bin/{Configuration}");
            foreach (var directory in directories)
            {
                var di = new DirectoryInfo(directory);
                var pluginName = di.Parent?.Parent?.Name;
                plugins.Add(pluginName);

                Directory.CreateDirectory(OutputDirectory / "Artifacts" / "Plugins" / pluginName);
                Serilog.Log.Information(pluginName);
                var files = di.GetFiles("*.dll");
                foreach (var file in files)
                {
                    string outFile = string.Empty;

                    if (file.Name.StartsWith(pluginName))
                    {
                        outFile = OutputDirectory / "Artifacts" / "Plugins" / pluginName /
                                  $"{Path.GetFileNameWithoutExtension(file.Name)}_plugin.dll";
                    }
                    else
                    {
                        outFile = OutputDirectory / "Artifacts" / "Plugins" / pluginName / file.Name;
                    }

                    if (file.Name.StartsWith("aimp_dotnet"))
                    {
                        outFile = OutputDirectory / "Artifacts" / "Plugins" / pluginName / $"{pluginName}.dll";
                    }

                    Serilog.Log.Information($"Copy '{file.FullName}' to '{outFile}'");
                    file.CopyTo(outFile, true);
                }
            }

            Serilog.Log.Information("Copy SDK files to artifacts folder");
            var sdkFolder = new DirectoryInfo(SourceDirectory / $"{Configuration}");
            Directory.CreateDirectory(OutputDirectory / "Artifacts" / "SDK");
            var sdkFiles = sdkFolder.GetFiles("*.dll");
            foreach (var file in sdkFiles)
            {
                var outFile = OutputDirectory / "Artifacts" / "SDK" / file.Name;
                file.CopyTo(outFile, true);
            }

            Serilog.Log.Information("Validate output");

            bool validatePluginFolder(string plugin, IEnumerable<FileInfo> files)
            {
                var isValid = true;

                isValid &= files.Any(c => c.Name.StartsWith("AIMP.SDK"));
                isValid &= files.Any(c => c.Name == $"{plugin}.dll");
                isValid &= files.Any(c => c.Name == $"{plugin}_plugin.dll");

                return isValid;
            }

            var isValid = true;
            foreach (var plugin in plugins)
            {
                var pluginFolder = OutputDirectory / "Artifacts" / "Plugins" / plugin;
                var di = new DirectoryInfo(pluginFolder);
                var files = di.GetFiles("*.dll");
                if (!validatePluginFolder(plugin, files))
                {
                    Serilog.Log.Error($"Plugin {plugin} not valid.");
                    isValid = false;
                }
            }

            Assert.True(isValid, "Artifacts not valid");
            Serilog.Log.Information("Compress artifacts");
            ZipFile.CreateFromDirectory(OutputDirectory / "Artifacts", OutputDirectory / "aimp.sdk.zip");

            if (IsTeamCity)
            {
                if (!isValid)
                {
                    TeamCity.Instance.AddBuildProblem("Unable to create artifacts");
                }

                TeamCity.Instance.PublishArtifacts(OutputDirectory / "aimp.sdk.zip");
            }
        });

    void PrintParameters(string prefix)
    {
        var buildType = GetType();
        ((TypeInfo)buildType).DeclaredMembers
            .Where(c => c.Name.StartsWith(prefix) && c.MemberType == MemberTypes.Field)
            .NotNull()
            .ForEach(info =>
            {
                Serilog.Log.Information(ParameterOutputPattern, info.Name, info.GetValue(this));
            });
    }
}
