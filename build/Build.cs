using System.IO;
using System.IO.Compression;
using System.Linq;
using Nuke.Common.Git;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.InspectCode;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Core;
using Nuke.Core.Tooling;
using Nuke.Core.Utilities;
using Nuke.Core.Utilities.Collections;
using SonarQube;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;
using static Nuke.Core.IO.FileSystemTasks;
using static Nuke.Core.IO.PathConstruction;
using SonarQubeTasks = SonarQube.SonarQubeTasks;

class Build : NukeBuild
{
    [Parameter("Indicates to push to nuget.org feed.")] readonly bool NuGet;

    [Parameter("ApiKey for the specified source.")] readonly string ApiKey;

    [GitVersion(DisableOnUnix = true)] readonly GitVersion GitVersion;
    [GitRepository(Branch = "master")] readonly GitRepository GitRepository;

    [Parameter] readonly string SonarUrl;
    [Parameter] readonly string SonarUser;
    [Parameter] readonly string SonarPassword;
    [Parameter] readonly string SonarProjectKey;
    [Parameter] readonly string SonarProjectName;

    private string Source => NuGet
        ? "https://api.nuget.org/v3/index.json"
        : "https://www.myget.org/F/aimpsdk/api/v2/package";

    // Console application entry. Also defines the default target.
    public static int Main () => Execute<Build>(x => x.Compile);

    Target Clean => _ => _
            .Executes(() =>
            {
                DeleteDirectories(GlobDirectories(SourceDirectory, "**/bin", "**/obj"));
                EnsureCleanDirectory(OutputDirectory);
            });

    Target Restore => _ => _
            .DependsOn(Clean)
            .Executes(() =>
            {
                MSBuild(s => DefaultMSBuildRestore);
            });

    Target Compile => _ => _
            .DependsOn(Restore, Version)
            .Requires(() => GitVersion != null)
            .Executes(() =>
            {
                MSBuild(s => DefaultMSBuildCompile.SetNodeReuse(false));
            });

    Target Version => _ => _
        .Executes(() =>
        {
            var properties = GlobDirectories(SourceDirectory, "**/Properties");
            foreach (var property in properties)
            {
                ProcessTasks.StartProcess(GitVersionTasks.DefaultGitVersion.ToolPath, $"/updateassemblyinfo {property}/AssemblyInfo.cs");
            }

            var rcFile = SourceDirectory / "aimp_dotnet"/ "aimp_dotnet.rc";
            if (File.Exists(rcFile))
            {
                Logger.Info($"Update version for '{rcFile}'");
                var fileContent = File.ReadAllText(rcFile);
                fileContent = fileContent.Replace("1,0,0,1", GitVersion.AssemblySemVer).Replace("1.0.0.1", GitVersion.AssemblySemVer);
                File.WriteAllText(rcFile, fileContent);
            }
        });

    Target Pack => _ => _
        .Executes(() =>
        {
            Logger.Info("Start build Nuget packages");

            NuGetTasks.NuGetPack(c => NuGetTasks.DefaultNuGetPack
                .SetTargetPath(RootDirectory / "AimpSDK.nuspec")
                .SetBasePath(RootDirectory));

            NuGetTasks.NuGetPack(c => NuGetTasks.DefaultNuGetPack
                .SetTargetPath(RootDirectory / "AimpSDK.symbols.nuspec")
                .SetBasePath(RootDirectory)
                .AddProperty("Symbols", string.Empty));

            NuGetTasks.NuGetPack(c => NuGetTasks.DefaultNuGetPack
                .SetTargetPath(RootDirectory / "AimpSDK.sources.nuspec")
                .SetBasePath(RootDirectory));
        });

    Target Publish => _ => _
        .Requires(() => ApiKey)
        .Requires(() => !NuGet || GitVersionAttribute.Bump.HasValue)
        .Requires(() => !NuGet || Configuration.EqualsOrdinalIgnoreCase("release"))
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
        .DependsOn(Restore)
        .Executes(() =>
        {
            InspectCodeTasks.InspectCode(s => s.AddExtensions(
                "EtherealCode.ReSpeller",
                "PowerToys.CyclomaticComplexity",
                "ReSharper.ImplicitNullability",
                "ReSharper.SerializationInspections",
                "ReSharper.XmlDocInspections"));
        });

    Target SonarQube => _ => _
        .DependsOn(Restore)
        .Requires(() => SonarUrl, () => SonarUser)
        .Executes(() =>
        {
            SonarQubeTasks.SonarQubeBegin(c => c
                .SetProjectBaseDir(SourceDirectory)
                .SetWorkingDirectory(SourceDirectory)
                .SetHostUrl(SonarUrl)
                .SetProjectKey(SonarProjectKey)
                .SetProjectName(SonarProjectName)
                .SetUserName(SonarUser)
                .SetUserPassword(SonarPassword)
                .EnableVerbose(), new ProcessSettings());
        }, () =>
        {
            MSBuild(s => DefaultMSBuildCompile.SetNodeReuse(false));
        }, () =>
        {
            SonarQubeTasks.SonarQubeEnd(c => c
                .SetUserName(SonarUser)
                .SetUserPassword(SonarPassword)
                .SetWorkingDirectory(SourceDirectory)
            );
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
