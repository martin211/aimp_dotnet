using System.IO;
using System.Linq;
using Nuke.Common.Git;
using Nuke.Common.Tools.DocFx;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.InspectCode;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Core;
using Nuke.Core.Tooling;
using Nuke.Core.Utilities;
using Nuke.Core.Utilities.Collections;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;
using static Nuke.Core.IO.FileSystemTasks;
using static Nuke.Core.IO.PathConstruction;

class Build : NukeBuild
{
    [Parameter("Indicates to push to nuget.org feed.")] readonly bool NuGet;

    [Parameter("ApiKey for the specified source.")] readonly string ApiKey;

    [GitVersion(DisableOnUnix = true)] readonly GitVersion GitVersion;
    [GitRepository(Branch = "master")] readonly GitRepository GitRepository;

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
                fileContent = fileContent.Replace("1,0,0,1", Nuke.Common.Tools.GitVersion.GitVersion.AssemblySemVer).Replace("1.0.0.1", Nuke.Common.Tools.GitVersion.GitVersion.AssemblySemVer);
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
        .Requires(() => !NuGet || GitVersion.BranchName.Equals("master"))
        .Executes(() =>
        {
            Logger.Info("Deploying Nuget packages");

            //var packages = Directory.GetFiles(OutputDirectory, "AimpSDK.*");
            //foreach (var package in packages)
            //{
            //    NuGetTasks.NuGetPush(c => c
            //        .SetTargetPath(package)
            //        .SetApiKey(ApiKey)
            //        .SetSymbolApiKey(ApiKey)
            //        .SetSource("https://www.myget.org/F/aimpsdk/api/v2/package")
            //        .SetSymbolSource("https://www.myget.org/F/aimpsdk/symbols/api/v2/package"));
            //}
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
}
