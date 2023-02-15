//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Reflection;
using Microsoft.Build.Tasks;
using Nuke.Common;
using Nuke.Common.CI.GitLab;
using Nuke.Common.CI.TeamCity;
using Nuke.Common.Execution;
using Nuke.Common.Git;
using Nuke.Common.IO;
using Nuke.Common.ProjectModel;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.Git;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Common.Utilities;
using Nuke.Common.Utilities.Collections;
using Octokit;
using Serilog;
using static Nuke.Common.IO.FileSystemTasks;
using static Nuke.Common.IO.PathConstruction;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;

[CheckBuildProjectConfigurations]
partial class Build : NukeBuild
{
    [Parameter("Configuration to build - Default is 'Debug' (local) or 'Release' (server)")]
    readonly Configuration Configuration = IsLocalBuild ? Configuration.Debug : Configuration.Release;

    [Solution] readonly Solution Solution;
    [GitRepository] readonly GitRepository GitRepository;
    [GitVersion(NoFetch = true, UpdateAssemblyInfo = false, UpdateBuildNumber = false)]
    readonly GitVersion GitVersion;

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
    [Parameter] readonly MSBuildTargetPlatform TargetPlatform = MSBuildTargetPlatform.x86;

    [Parameter]
    readonly string MsBuildPath =
        @"c:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MsBuild.exe";

    #endregion

    bool IsTeamCity => TeamCity.Instance != null;

    bool IsGItLab => GitLab.Instance != null;

    string BuildNumber
    {
        get
        {
            if (IsTeamCity)
            {
                return TeamCity.Instance.BuildNumber;
            }

            if (IsGItLab)
            {
                return GitLab.Instance.JobId.ToString();
            }

            return string.Empty;
        }
    }

    AbsolutePath SourceDirectory => RootDirectory / "src";
    AbsolutePath TestsDirectory => RootDirectory / "tests";
    AbsolutePath OutputDirectory => RootDirectory / "output";

    AbsolutePath PvsReportPath => OutputDirectory / "aimpDotNet.plog";

    AbsolutePath SDKBinFolder => SourceDirectory / "SDK/aimp_dotnet/bin/";

    readonly string MasterBranch = "master";
    readonly string DevelopBranch = "develop";
    readonly string ReleaseBranchPrefix = "release";
    readonly string HotfixBranchPrefix = "hotfix";
    readonly string MailstoneBranch = "mailstone";
    string _version = "1.0.0.0";
    string _buildNumber = "1.0.0.0";

    string ParameterOutputPattern = "Parameter {parameter}: {value}";

    bool IsReleaseBuild => GitRepository.Branch.StartsWith(ReleaseBranchPrefix);

    public static int Main() => Execute<Build>(x => x.Compile);

    Target PrintBuildParameters => _ => _
        .Executes(() =>
        {
            PrintParameters("Sonar");
            PrintParameters("Nuget");
            PrintParameters("Request");
            PrintParameters("IntegrationTest");

            Log.Information("Git information");
            Log.Information("Git Branch: {Branch}", GitRepository.Branch);
            Log.Information("Git Commit: {Commit}", GitRepository.Commit);

            Log.Information("Git version");
            var type = GitVersion.GetType();

            ((TypeInfo)type).DeclaredProperties.Where(c => c.MemberType == MemberTypes.Property)
                .NotNull()
                .ForEach(info =>
                {
                    Log.Information(ParameterOutputPattern, info.Name, info.GetValue(GitVersion));
                });
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
        .Triggers(UpdateBuildNumber)
        .Executes(() =>
        {
            GetVersion();

            Log.Information("Version: {_version}", _version);
            var assemblyInfo = SourceDirectory / "AssemblyInfo.cs";
            if (File.Exists(assemblyInfo))
            {
                Log.Information("Update version for '{assemblyInfo}'", assemblyInfo);
                var fileContent = File.ReadAllText(assemblyInfo);
                fileContent = fileContent.Replace("1.0.0.0", _version);
                File.WriteAllText(assemblyInfo, fileContent);
            }

            var rcFile = SourceDirectory / "aimp_dotnet" / "aimp_dotnet.rc";
            if (File.Exists(rcFile))
            {
                Log.Information("Update version for '{rcFile}'", rcFile);
                var fileContent = File.ReadAllText(rcFile);
                fileContent = fileContent.Replace("1,0,0,1", _version.Replace(".", ",")).Replace("1.0.0.1", _version);
                File.WriteAllText(rcFile, fileContent);
            }
        });

    Target Compile => _ => _
        .DependsOn(PrintBuildParameters, Restore, Version)
        .Triggers(UpdateBuildNumber)
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
                .SetNodeReuse(IsLocalBuild)
                .SetTargetPlatform(TargetPlatform));
        });

    Target Pack => _ => _
        .DependsOn(Version)
        .Executes(() =>
        {
            Log.Information("Start build Nuget packages");

            var nugetFolder = RootDirectory / "Nuget";

            var config = new NuGetPackSettings()
                .SetBasePath(RootDirectory)
                .SetConfiguration(Configuration)
                .SetVersion(_version)
                .SetOutputDirectory(OutputDirectory);

            if (GitRepository.Branch != null && !GitRepository.Branch.Contains(ReleaseBranchPrefix))
            {
                config = config.SetSuffix(GitVersion.PreReleaseTag);
            }

            if (TargetPlatform == MSBuildTargetPlatform.x86)
            {
                Log.Information("Pack X86 package");
                NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK.nuspec"));
                NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK.nuspec").EnableSymbols());
                //NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK.symbols.nuspec"));
                NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK.sources.nuspec"));
            }

            if (TargetPlatform == MSBuildTargetPlatform.x64)
            {
                Log.Information("Pack X64 package");
                NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK-x64.nuspec"));
            }

            if (IsTeamCity)
            {
                var dir = new DirectoryInfo(OutputDirectory);

                foreach (var fileInfo in dir.GetFiles("*.nupkg"))
                {
                    TeamCity.Instance.PublishArtifacts(fileInfo.FullName);
                }
            }
        });

    Target Publish => _ => _
        .Requires(() => Configuration.Equals(Configuration.Release))
        .Requires(() => NugetApiKey)
        .Executes(() =>
        {
            PrintParameters("Nuget");

            Log.Information("Deploying Nuget packages");
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
        .Requires(() => TargetPlatform)
        .Executes(() =>
        {
            List<string> plugins = new List<string>();

            var isValid = true;

            var targetPlatform = TargetPlatform.ToString();

            EnsureCleanDirectory(OutputDirectory / targetPlatform);

            Log.Information("Target platform {platform}", targetPlatform);
            var artifactsFolder = OutputDirectory / targetPlatform;

            Directory.CreateDirectory(artifactsFolder);

            Log.Information("Copy plugins to artifacts folder");

            var directories = GlobDirectories(SourceDirectory / "Plugins", $"**/bin/{targetPlatform}/{Configuration}");
            foreach (var directory in directories)
            {
                var pluginDirectory = new DirectoryInfo(directory);
                var pluginName = pluginDirectory.Parent?.Parent?.Parent?.Name;
                plugins.Add(pluginName);

                Directory.CreateDirectory(artifactsFolder / "Plugins" / pluginName);
                Log.Information(pluginName);
                var files = pluginDirectory.GetFiles("*.dll");
                foreach (var file in files)
                {
                    string outFile = string.Empty;

                    if (file.Name.StartsWith(pluginName))
                    {
                        outFile = artifactsFolder / "Plugins" / pluginName / $"{Path.GetFileNameWithoutExtension(file.Name)}_plugin.dll";
                    }
                    else
                    {
                        outFile = artifactsFolder / "Plugins" / pluginName / file.Name;
                    }

                    if (file.Name.StartsWith("aimp_dotnet"))
                    {
                        outFile = artifactsFolder / "Plugins" / pluginName / $"{pluginName}.dll";
                    }

                    Log.Information($"Copy '{file.FullName}' to '{outFile}'");
                    file.CopyTo(outFile, true);
                }
            }

            var sdkFolder = new DirectoryInfo(SDKBinFolder / $"{targetPlatform}/{Configuration}");
            Log.Information($"Copy SDK files to artifacts folder '{sdkFolder}'");

            Directory.CreateDirectory(artifactsFolder / "SDK");
            var sdkFiles = sdkFolder.GetFiles("*.dll");
            foreach (var file in sdkFiles)
            {
                var outFile = artifactsFolder / "SDK" / file.Name;
                file.CopyTo(outFile, true);
            }

            Log.Information("Validate output");

            bool validatePluginFolder(string plugin, IEnumerable<FileInfo> files)
            {
                var isValid = true;

                isValid &= files.Any(c => c.Name.StartsWith("AIMP.SDK"));
                isValid &= files.Any(c => c.Name == $"{plugin}.dll");
                isValid &= files.Any(c => c.Name == $"{plugin}_plugin.dll");

                return isValid;
            }

            foreach (var plugin in plugins)
            {
                var pluginFolder = artifactsFolder / "Plugins" / plugin;
                var di = new DirectoryInfo(pluginFolder);
                var files = di.GetFiles("*.dll");
                if (!validatePluginFolder(plugin, files))
                {
                    Log.Error($"Plugin {plugin} not valid.");
                    isValid = false;
                }
            }

            Assert.True(isValid, $"Artifacts not valid. Platform '{targetPlatform}'");

            var outputSkdFile = $"aimp.sdk-{targetPlatform}.zip";

            Log.Information($"Compress artifacts to '{outputSkdFile}'");

            if (File.Exists(OutputDirectory / outputSkdFile))
            {
                File.Delete(OutputDirectory / outputSkdFile);
            }

            ZipFile.CreateFromDirectory(artifactsFolder, OutputDirectory / outputSkdFile);

            if (IsTeamCity)
            {
                TeamCity.Instance.PublishArtifacts(OutputDirectory / outputSkdFile);
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
                Log.Information(ParameterOutputPattern, info.Name, info.GetValue(this));
            });
    }

    void GetVersion()
    {
        if (GitRepository.Branch.StartsWith(MailstoneBranch))
        {
            _version = GitRepository.Branch
                .Replace($"{MailstoneBranch}_", string.Empty)
                .Replace("_", ".");

            _buildNumber = $"{_version}{(!string.IsNullOrWhiteSpace(GitVersion.BuildMetaData) ? "." : string.Empty)}{GitVersion.BuildMetaData}";
        }
        else if (GitRepository.Branch.StartsWith(ReleaseBranchPrefix))
        {
            _version = GitRepository.Branch.Split("/")[1];
            _buildNumber = $"{_version}{(!string.IsNullOrWhiteSpace(GitVersion.BuildMetaData) ? "." : string.Empty)}{GitVersion.BuildMetaData}";
        }
        else
        {
            string tag = string.Empty;

            var process = ProcessTasks.StartProcess("git", "ls-remote --tags --sort=-committerdate ./.");
            process.WaitForExit();
            var output = process.Output;

            if (output.Count > 0)
            {
                var outText = output.First().Text;
                tag = outText.Substring(outText.LastIndexOf("/") + 1, outText.Length - outText.LastIndexOf("/") - 1);
            }

            if (!string.IsNullOrWhiteSpace(tag))
            {
                var patchVersion = int.Parse(tag.Split(".").Last()) + 1;
                _version = tag.Substring(0, tag.LastIndexOf(".")) + $".{patchVersion}";
                _buildNumber = $"{_version}{GitVersion.PreReleaseTagWithDash}";
            }
            else
            {
                _buildNumber = $"{_version}{(!string.IsNullOrWhiteSpace(GitVersion.BuildMetaData) ? "." : string.Empty)}{GitVersion.BuildMetaData}";
                _version = BuildNumber;
            }
        }
    }

    Target UpdateBuildNumber => _ => _
        .Executes(() =>
        {
            if (IsTeamCity)
            {
                Log.Information("Set build version: {version}", _buildNumber);
                TeamCity.Instance.SetBuildNumber(_buildNumber);
                TeamCity.Instance.SetEnvironmentVariable("BUILD_NUMBER", _buildNumber);
            }
        });
}
