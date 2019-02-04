using System;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text.RegularExpressions;
using Aimp.DotNet.Build;
using Nuke.Common;
using Nuke.Common.Git;
using Nuke.Common.ProjectModel;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.InspectCode;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Common.Tools.SonarScanner;
using Nuke.Common.Utilities;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.IO.FileSystemTasks;
using static Nuke.Common.IO.PathConstruction;

class Build : NukeBuild
{
    [Parameter("Indicates to push to nuget.org feed.")] readonly bool NuGet;
    [Parameter("ApiKey for the specified source.")] readonly string ApiKey;
    [Parameter] readonly string SonarUrl;
    [Parameter] readonly string SonarUser;
    [Parameter] readonly string SonarPassword;
    [Parameter] readonly string SonarProjectKey;
    [Parameter] readonly string SonarProjectName;
    [Parameter] readonly string VmWareMachine;
    [Parameter] readonly string BuildConfiguration;

    private string Source => NuGet
        ? "https://api.nuget.org/v3/index.json"
        : "https://www.myget.org/F/aimpsdk/api/v2/package";

    readonly string MasterBranch = "master";
    readonly string DevelopBranch = "develop";
    readonly string ReleaseBranchPrefix = "release";
    readonly string HotfixBranchPrefix = "hotfix";

    public static int Main() => Execute<Build>(x => x.Compile);

    [Parameter("Configuration to build - Default is 'Debug' (local) or 'Release' (server)")]
    private Configuration Configuration = IsLocalBuild ? Configuration.Debug : Configuration.Release;

    //readonly Configuration Configuration = string.IsNullOrWhiteSpace(BuildConfiguration)
    //    ? (IsLocalBuild ? Configuration.Debug : Configuration.Release)
    //    : BuildConfiguration.Equals("release", StringComparison.InvariantCultureIgnoreCase) ? Configuration.Release : Configuration.Debug;

    [Solution] readonly Solution Solution;
    [GitRepository] readonly GitRepository GitRepository;
    [GitVersion] readonly GitVersion GitVersion;

    AbsolutePath SourceDirectory => RootDirectory / "src";
    AbsolutePath OutputDirectory => RootDirectory / "output";

    Target Clean => _ => _
        .Executes(() =>
        {
            DeleteDirectories(GlobDirectories(SourceDirectory, "**/bin", "**/obj"));
            EnsureCleanDirectory(OutputDirectory);
        });

    Target SetConfiguration => _ => _
        .Executes(() =>
        {
            Configuration = !string.IsNullOrWhiteSpace(BuildConfiguration) &&
                            BuildConfiguration.Equals("release", StringComparison.OrdinalIgnoreCase)
                ? Configuration.Release
                : Configuration.Debug;
        });

    Target Compile => _ => _
        .DependsOn(SetConfiguration, Version)
        .Requires(() => GitVersion != null)
        .Executes(() =>
        {
            MSBuildTasks.MSBuild(s => s
                .SetNodeReuse(false)
                .SetRestore(true)
                .SetProjectFile(Solution)
                .SetAssemblyVersion(GitVersion.GetNormalizedAssemblyVersion())
                .SetFileVersion(GitVersion.GetNormalizedFileVersion())
                .SetInformationalVersion(GitVersion.InformationalVersion)
                .SetConfiguration(Configuration));
        });

    Target Version => _ => _
        .DependsOn(SetConfiguration)
        .Executes(() =>
        {
            var properties = GlobDirectories(SourceDirectory, "**/Properties");
            foreach (var property in properties)
            {
                ProcessTasks.StartProcess(GitVersionTasks.GitVersionPath, $"/updateassemblyinfo {property}/AssemblyInfo.cs");
            }

            var rcFile = SourceDirectory / "aimp_dotnet" / "aimp_dotnet.rc";
            if (File.Exists(rcFile))
            {
                Logger.Info($"Update version for '{rcFile}'");
                var fileContent = File.ReadAllText(rcFile);
                fileContent = fileContent.Replace("1,0,0,1", GitVersion.AssemblySemVer).Replace("1.0.0.1", GitVersion.AssemblySemVer);
                File.WriteAllText(rcFile, fileContent);
            }
        });

    Target Pack => _ => _
        .DependsOn(SetConfiguration)
        .Executes(() =>
        {
            Logger.Info("Start build Nuget packages");

            var nugetFolder = RootDirectory / "Nuget";
            var version = GitRepository.Branch.Equals(MasterBranch) || GitRepository.Branch.Equals(DevelopBranch)
                ? GitVersion.NuGetVersionV2
                : $"{GitVersion.AssemblySemVer}-beta";

            NuGetTasks.NuGetPack(c => c
                .SetTargetPath(nugetFolder / "AimpSDK.nuspec")
                .SetBasePath(RootDirectory)
                .SetConfiguration(Configuration)
                .SetVersion(version)
                .SetOutputDirectory(OutputDirectory));

            NuGetTasks.NuGetPack(c => c
                .SetTargetPath(nugetFolder / "AimpSDK.symbols.nuspec")
                .SetBasePath(RootDirectory)
                .SetVersion(version)
                .SetConfiguration(Configuration)
                .SetOutputDirectory(OutputDirectory)
                .AddProperty("Symbols", string.Empty));

            NuGetTasks.NuGetPack(c => c
                .SetTargetPath(nugetFolder / "AimpSDK.sources.nuspec")
                .SetVersion(version)
                .SetConfiguration(Configuration)
                .SetBasePath(RootDirectory)
                .SetOutputDirectory(OutputDirectory));
        });

    Target Publish => _ => _
        .DependsOn(SetConfiguration)
        .Requires(() => ApiKey)
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
                    .SetSource(Source)
                    .SetApiKey(ApiKey)));
        });

    Target Analysis => _ => _
        .DependsOn(SetConfiguration)
        .Executes(() =>
        {
            InspectCodeTasks.InspectCode(s => s.AddExtensions(
                "EtherealCode.ReSpeller",
                "PowerToys.CyclomaticComplexity",
                "ReSharper.ImplicitNullability",
                "ReSharper.SerializationInspections",
                "ReSharper.XmlDocInspections"));
        }
      );

    Target SonarQube => _ => _
      .DependsOn(SetConfiguration)
      .Requires(() => SonarUrl, () => SonarUser)
      .Executes(() =>
      {
          var configuration = new SonarBeginSettings();
          configuration
              .SetProjectKey(SonarProjectKey)
              .SetIssueTrackerUrl(SonarUrl)
              .SetServer(SonarUrl)
              //.SetHomepage(SonarUrl)
              .SetLogin(SonarUser)
              .SetPassword(SonarPassword)
              .SetName(SonarProjectName)
              .SetWorkingDirectory(SourceDirectory)
              .SetVerbose(true);

          configuration = configuration.SetProjectBaseDir(SourceDirectory);

          SonarScannerTasks.SonarScannerBegin(c => configuration);
      }, () =>
      {
          MSBuildTasks.MSBuild(c => c
              .SetConfiguration(Configuration)
              .SetTargets("Rebuild")
              .SetNodeReuse(true));
      }, () =>
      {
          SonarScannerTasks.SonarScannerEnd(c => c
              .SetLogin(SonarUser)
              .SetPassword(SonarPassword)
              .SetWorkingDirectory(SourceDirectory)
          );
      });

    Target Artifacts => _ => _
        .DependsOn(SetConfiguration)
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

    Target PvsStudio => _ => _
        .DependsOn(SetConfiguration)
        .Executes(() =>
        {
            ProcessTasks.StartProcess("git", $"checkout {DevelopBranch}");
            ProcessTasks.StartProcess("git", $"branch -d pvs_{GitVersion.AssemblySemVer}");
            ProcessTasks.StartProcess(
                "git",
                $"checkout -b pvs_{GitVersion.AssemblySemVer}",
                SourceDirectory);

            ProcessTasks.StartProcess(
                "PVS-Studio_Cmd",
                $"--target {Solution} --configuration {Configuration} --output {OutputDirectory / "dot_net.plog"}",
                SourceDirectory).WaitForExit();
        });

    Target RunVmWare => _ => _
        .Executes(() =>
        {
            bool CheckVmRunning()
            {
                bool isRunning = true;
                bool checkVm = false;

                ProcessTasks.StartProcess(
                        "vmrun.exe",
                        "list",
                        null,
                        null,
                        null,
                        true,
                        ((type, s) =>
                        {
                            var m = Regex.Match(s, @"^.+: (\d)$");
                            if (m.Success)
                            {
                                var count = int.Parse(m.Groups[1].Value);
                                checkVm = count > 0;
                            }

                            if (checkVm && s.Contains(VmWareMachine))
                            {
                                isRunning = false;
                            }
                        }))
                    ?.WaitForExit();

                return isRunning;
            }

            if (!CheckVmRunning())
            {
                Logger.Info($"Starting Virtual Machine: {VmWareMachine}");
                ProcessTasks.StartProcess("vmrun.exe", $"start \"{VmWareMachine}\" nogui")?.WaitForExit();
                if (!CheckVmRunning())
                {
                    Logger.Error($"Unable run machine: {VmWareMachine}");
                }
            }
        });
}
