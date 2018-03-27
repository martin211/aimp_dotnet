using System.IO;
using Nuke.Common.Tools.DocFx;
using Nuke.Common.Tools.Git;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Core;
using Nuke.Core.Tooling;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;
using static Nuke.Core.IO.FileSystemTasks;
using static Nuke.Core.IO.PathConstruction;

class Build : NukeBuild
{
    // Console application entry. Also defines the default target.
    public static int Main () => Execute<Build>(x => x.Deploy);

    // Auto-injection fields:

    [GitVersion] readonly GitVersion GitVersion;
    // Semantic versioning. Must have 'GitVersion.CommandLine' referenced.

    // [GitRepository] readonly GitRepository GitRepository;
    // Parses origin, branch name and head from git config.

    [Parameter] readonly string MyGetApiKey;
    // Returns command-line arguments and environment variables.

    Target Clean => _ => _
            .OnlyWhen(() => false) // Disabled for safety.
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
            .DependsOn(Restore)
            .DependsOn(Version)
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

            var rcFile = SourceDirectory / "aimp_dotnet/aimp_dotnet.rc";
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

    Target Deploy => _ => _
        .Executes(() =>
        {
            Logger.Info("Deploying Nuget packages");

            var packages = Directory.GetFiles(OutputDirectory, "AimpSDK.*");
            foreach (var package in packages)
            {
                NuGetTasks.NuGetPush(c => c
                    .SetTargetPath(package)
                    .SetApiKey(MyGetApiKey)
                    .SetSymbolApiKey(MyGetApiKey)
                    .SetSource("https://www.myget.org/F/aimpsdk/api/v2/package")
                    .SetSymbolSource("https://www.myget.org/F/aimpsdk/symbols/api/v2/package"));
            }
        });

    Target BuildDocumentation => _ => _
        .DependsOn(Compile)
        .Executes(() =>
        {
            DocFxTasks.DocFxBuild(RootDirectory / "docs/docfx.json");
        });

    //Target PublishDocumentation => _ => _
    //    .Executes(() =>
    //    {
    //    });
}
