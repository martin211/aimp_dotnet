using System;
using System.IO;
using System.IO.Compression;
using System.Linq;
using Aimp.DotNet.Build;
using Nuke.Common;
using Nuke.Common.CI.GitLab;
using Nuke.Common.CI.TeamCity;
using Nuke.Common.Execution;
using Nuke.Common.Git;
using Nuke.Common.IO;
using Nuke.Common.ProjectModel;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Common.Tools.SonarScanner;
using Nuke.Common.Utilities;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.EnvironmentInfo;
using static Nuke.Common.IO.FileSystemTasks;
using static Nuke.Common.IO.PathConstruction;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;

[CheckBuildProjectConfigurations]
[UnsetVisualStudioEnvironmentVariables]
partial class Build : NukeBuild
{
    /// Support plugins are available for:
    ///   - JetBrains ReSharper        https://nuke.build/resharper
    ///   - JetBrains Rider            https://nuke.build/rider
    ///   - Microsoft VisualStudio     https://nuke.build/visualstudio
    ///   - Microsoft VSCode           https://nuke.build/vscode

    public static int Main() => Execute<Build>(x => x.Compile);

    [Parameter("Configuration to build - Default is 'Debug' (local) or 'Release' (server)")]
    readonly Configuration Configuration = IsLocalBuild ? Configuration.Debug : Configuration.Release;

    [Solution] readonly Solution Solution;
    [GitRepository] readonly GitRepository GitRepository;
    [GitVersion(NoFetch = true, UpdateAssemblyInfo = true)] readonly GitVersion GitVersion;

    [Parameter] readonly string SonarUrl;
    [Parameter] readonly string SonarUser;
    [Parameter] readonly string SonarPassword;
    [Parameter] readonly string SonarProjectKey;
    [Parameter] readonly string SonarProjectName;

    [Parameter] readonly string Source;

    AbsolutePath SourceDirectory => RootDirectory / "src";
    AbsolutePath TestsDirectory => RootDirectory / "tests";
    AbsolutePath OutputDirectory => RootDirectory / "output";

    readonly string MasterBranch = "master";
    readonly string DevelopBranch = "develop";
    readonly string ReleaseBranchPrefix = "release";
    readonly string HotfixBranchPrefix = "hotfix";

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
            MSBuild(_ => _
                .SetTargetPath(Solution)
                .SetTargets("Restore"));
        });

    Target Version => _ => _
        .Executes(() =>
        {
            var rcFile = SourceDirectory / "aimp_dotnet" / "aimp_dotnet.rc";
            if (File.Exists(rcFile))
            {
                Logger.Info($"Update version for '{rcFile}'");
                Logger.Info($"Assembly version: {GitVersion.AssemblySemVer}");
                var fileContent = File.ReadAllText(rcFile);
                fileContent = fileContent.Replace("1,0,0,1", GitVersion.AssemblySemVer).Replace("1.0.0.1", GitVersion.AssemblySemVer);
                File.WriteAllText(rcFile, fileContent);
            }
        });

    Target Compile => _ => _
        .DependsOn(Restore, Version)
        .Executes(() =>
        {
            MSBuild(_ => _
                .SetTargetPath(Solution)
                .SetTargets("Rebuild")
                .SetConfiguration(Configuration)
                .SetAssemblyVersion(GitVersion.AssemblySemVer)
                .SetFileVersion(GitVersion.AssemblySemFileVer)
                .SetInformationalVersion(GitVersion.InformationalVersion)
                .SetMaxCpuCount(Environment.ProcessorCount)
                .SetNodeReuse(IsLocalBuild));
        });

    Target SonarQube => _ => _
    .Requires(() => SonarUrl, () => SonarUser, () => SonarProjectKey, () => SonarProjectName)
    .DependsOn(Restore)
    .Executes(() =>
    {
        var framework = "sonar-scanner-msbuild-4.8.0.12008-net46";
        var configuration = new SonarBeginSettings()
                .SetProjectKey(SonarProjectKey)
                .SetIssueTrackerUrl(SonarUrl)
                .SetServer(SonarUrl)
                .SetVersion(GitVersion.AssemblySemVer)
                //.SetHomepage(SonarUrl)
                .SetLogin(SonarUser)
                .SetPassword(SonarPassword)
                .SetName(SonarProjectName)
                //.SetWorkingDirectory(SourceDirectory)
                .SetBranchName(GitRepository.Branch)
                .SetFramework(framework)
                .SetVerbose(false);

        if (GitRepository.Branch != null && !GitRepository.Branch.Contains(ReleaseBranchPrefix))
        {
            configuration = configuration.SetVersion(GitVersion.SemVer);
        }

        configuration = configuration.SetProjectBaseDir(SourceDirectory);

        var path = ToolPathResolver.GetPackageExecutable(
                packageId: "dotnet-sonarscanner|MSBuild.SonarQube.Runner.Tool",
                packageExecutable: "SonarScanner.MSBuild.exe",
                framework: framework);

        configuration = configuration.SetProcessToolPath(path);

        SonarScannerTasks.SonarScannerBegin(c => configuration);
    }, () =>
    {
        MSBuild(c => c
                .SetConfiguration(Configuration)
                .SetTargets("Rebuild")
                .SetSolutionFile(Solution)
                .SetNodeReuse(true));
    },
        () =>
        {
            var framework = "sonar-scanner-msbuild-4.8.0.12008-net46";
            var path = ToolPathResolver.GetPackageExecutable(
                packageId: "dotnet-sonarscanner|MSBuild.SonarQube.Runner.Tool",
                packageExecutable: "SonarScanner.MSBuild.exe",
                framework: framework);

            SonarScannerTasks.SonarScannerEnd(c => c
                .SetLogin(SonarUser)
                .SetPassword(SonarPassword)
                //.SetWorkingDirectory(SourceDirectory)
                .SetFramework(framework)
                .SetProcessToolPath(path));
        });

    Target Pack => _ => _
        .Executes(() =>
        {
            Logger.Info("Start build Nuget packages");

            var nugetFolder = RootDirectory / "Nuget";
            var version = GitVersion.AssemblySemVer;


            var config = new NuGetPackSettings()
                .SetBasePath(RootDirectory)
                .SetConfiguration(Configuration)
                .SetVersion(version)
                .SetOutputDirectory(OutputDirectory);

            if (GitRepository.Branch != null && !GitRepository.Branch.Contains(ReleaseBranchPrefix))
            {
                config = config.SetSuffix(GitVersion.PreReleaseTag);
            }

            if (Configuration == Configuration.Debug)
            {
                config = config.SetSuffix("debug");
            }

            NuGetTasks.NuGetPack(config
                .SetTargetPath(nugetFolder / "AimpSDK.nuspec"));

            NuGetTasks.NuGetPack(config
                .SetTargetPath(nugetFolder / "AimpSDK.symbols.nuspec")
                .AddProperty("Symbols", string.Empty));

            NuGetTasks.NuGetPack(config
                .SetTargetPath(nugetFolder / "AimpSDK.sources.nuspec"));
        });

    Target Publish => _ => _
    .Requires(() => Configuration.Equals(Configuration.Release))
    .Requires(() => GitRepository.Branch.EqualsOrdinalIgnoreCase(MasterBranch) ||
                    GitRepository.Branch.EqualsOrdinalIgnoreCase(DevelopBranch) ||
                    GitRepository.Branch.EqualsOrdinalIgnoreCase(ReleaseBranchPrefix) ||
                    GitRepository.Branch.EqualsOrdinalIgnoreCase(HotfixBranchPrefix))
    .Executes(() =>
    {
        Logger.Info("Deploying Nuget packages");
        GlobFiles(OutputDirectory, "*.nupkg").NotEmpty()
            .Where(c => !c.EndsWith("symbols.nupkg"))
            .ForEach(c => NuGetTasks.NuGetPush(s => s
                .SetTargetPath(c)
                .SetSource(Source)));
    });

    Target Artifacts => _ => _
     .Executes(() =>
     {
         EnsureCleanDirectory(OutputDirectory / "Artifacts");
         Directory.CreateDirectory(OutputDirectory / "Artifacts");

         Logger.Info("Copy plugins to artifacts folder");
         var directories = GlobDirectories(SourceDirectory / "Plugins", $"**/bin/{Configuration}");
         foreach (var directory in directories)
         {
             var di = new DirectoryInfo(directory);
             var pluginName = di.Parent?.Parent?.Name;

             Directory.CreateDirectory(OutputDirectory / "Artifacts" / "Plugins" / pluginName);

             var files = di.GetFiles("*.dll");
             foreach (var file in files)
             {
                 string outFile = string.Empty;

                 if (file.Name.StartsWith(pluginName))
                 {
                     outFile = OutputDirectory / "Artifacts" / "Plugins" / pluginName / $"{Path.GetFileNameWithoutExtension(file.Name)}_plugin.dll";
                 }
                 else
                 {
                     outFile = OutputDirectory / "Artifacts" / "Plugins" / pluginName / file.Name;
                 }

                 if (file.Name.StartsWith("aimp_dotnet"))
                 {
                     outFile = OutputDirectory / "Artifacts" / "Plugins" / pluginName / $"{pluginName}.dll";
                 }

                 file.CopyTo(outFile, true);
             }
         }

         Logger.Info("Copy SDK files to artifacts folder");
         var sdkFolder = new DirectoryInfo(SourceDirectory / $"{Configuration}");
         Directory.CreateDirectory(OutputDirectory / "Artifacts" / "SDK");
         var sdkFiles = sdkFolder.GetFiles("*.dll");
         foreach (var file in sdkFiles)
         {
             var outFile = OutputDirectory / "Artifacts" / "SDK" / file.Name;
             file.CopyTo(outFile, true);
         }

         Logger.Info("Compress artifacts");
         ZipFile.CreateFromDirectory(OutputDirectory / "Artifacts", OutputDirectory / "aimp.sdk.zip");
     });
}
