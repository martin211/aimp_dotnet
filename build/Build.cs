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
using Nuke.Common;
using Nuke.Common.CI.TeamCity;
using Nuke.Common.Execution;
using Nuke.Common.Git;
using Nuke.Common.IO;
using Nuke.Common.ProjectModel;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
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
    [Parameter] readonly MSBuildTargetPlatform TargetPlatform = MSBuildTargetPlatform.x86;

    [Parameter]
    readonly string MsBuildPath =
        @"c:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\MSBuild\Current\Bin\MsBuild.exe";

    #endregion

    bool IsTeamCity => TeamCity.Instance != null;

    AbsolutePath SourceDirectory => RootDirectory / "src";
    AbsolutePath TestsDirectory => RootDirectory / "tests";
    AbsolutePath OutputDirectory => RootDirectory / "output";

    AbsolutePath PvsReportPath => OutputDirectory / "aimpDotNet.plog";

    AbsolutePath SDKBinFolder => SourceDirectory / "SDK/aimp_dotnet/bin/";

    readonly string MasterBranch = "master";
    readonly string DevelopBranch = "develop";
    readonly string ReleaseBranchPrefix = "release";
    readonly string HotfixBranchPrefix = "hotfix";
    string _version = "1.0.0.0";

    string ParameterOutputPattern = "Parameter {parameter}: {value}";

    public static int Main() => Execute<Build>(x => x.Compile);

    Target PrintBuildParameters => _ => _
        .Executes(() =>
        {
            PrintParameters("Sonar");
            PrintParameters("Nuget");
            PrintParameters("Request");
            PrintParameters("IntegrationTest");
        });

    Target PrintDefaultBuildParameters => _ => _
        .Executes(() =>
        {
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
        .Executes(() =>
        {
            _version = GitRepository.Branch.StartsWith(ReleaseBranchPrefix)
                ? GitRepository.Branch.Split("/")[1]
                : GitVersion.AssemblySemVer;

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
                Log.Information("Assembly version: {AssemblySemVer}", GitVersion.AssemblySemVer);
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
        .DependsOn(PrintBuildParameters, PrintDefaultBuildParameters, Restore, Version)
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
                .SetTargetPlatform(MSBuildTargetPlatform.x86));
        });

    Target CompileX64 => _ => _
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
                .SetNodeReuse(IsLocalBuild)
                .SetTargetPlatform(MSBuildTargetPlatform.x64));
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
                config = config.SetSuffix("preview");
            }

            if (Configuration == Configuration.Debug)
            {
                config = config.SetSuffix("debug");
            }

            NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK.nuspec"));
            NuGetTasks.NuGetPack(config.SetTargetPath(nugetFolder / "AimpSDK-x64.nuspec"));
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
                TeamCity.Instance.SetBuildNumber(_version);
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
}
