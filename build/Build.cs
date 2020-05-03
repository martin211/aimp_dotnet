using System;
using System.IO;
using System.Linq;
using Aimp.DotNet.Build;
using Nuke.Common;
using Nuke.Common.Execution;
using Nuke.Common.Git;
using Nuke.Common.IO;
using Nuke.Common.ProjectModel;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Common.Tools.SonarScanner;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.EnvironmentInfo;
using static Nuke.Common.IO.FileSystemTasks;
using static Nuke.Common.IO.PathConstruction;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;

[CheckBuildProjectConfigurations]
[UnsetVisualStudioEnvironmentVariables]
class Build : NukeBuild
{
    /// Support plugins are available for:
    ///   - JetBrains ReSharper        https://nuke.build/resharper
    ///   - JetBrains Rider            https://nuke.build/rider
    ///   - Microsoft VisualStudio     https://nuke.build/visualstudio
    ///   - Microsoft VSCode           https://nuke.build/vscode

    public static int Main() => Execute<Build>(x => x.Compile);

    [Parameter("Configuration to build - Default is 'Debug' (local) or 'Release' (server)")]
    readonly Configuration Configuration = IsLocalBuild ? Configuration.Debug : Configuration.Release;

    [Parameter("Indicates to push to nuget.org feed.")] readonly bool NuGet;
    [Parameter("ApiKey for the specified source.")] readonly string ApiKey;
    [Parameter] readonly string SonarUrl = "http://sonar.uginnet.loc";
    [Parameter] readonly string SonarUser = "aadec67d1212daad96c8fccdb2a03724cb91a4e1";
    [Parameter] readonly string SonarPassword;
    [Parameter] readonly string SonarProjectKey = "AimpDotNetSDK";
    [Parameter] readonly string SonarProjectName = "Aimp_DotNetSDK";
    [Parameter] readonly string VmWareMachine;


    [Solution] readonly Solution Solution;
    [GitRepository] readonly GitRepository GitRepository;
    [GitVersion] readonly GitVersion GitVersion;

    AbsolutePath SourceDirectory => RootDirectory / "src";
    AbsolutePath OutputDirectory => RootDirectory / "output";
    string DocFxFile => RootDirectory / "documentation" / "docfx.json";

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
                    .SetFramework(framework)
                    .SetVerbose(false)
                    ;

                configuration = configuration.SetProjectBaseDir(SourceDirectory);

                var path = ToolPathResolver.GetPackageExecutable(
                    packageId: "dotnet-sonarscanner|MSBuild.SonarQube.Runner.Tool",
                    packageExecutable: "SonarScanner.MSBuild.exe",
                    framework: framework);

                configuration = configuration.SetToolPath(path);

                SonarScannerTasks.SonarScannerBegin(c => configuration);
            }, () =>
            {
                MSBuildTasks.MSBuild(c => c
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
                    .SetToolPath(path));
            });
}
