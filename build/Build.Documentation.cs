using System.Collections.Generic;
using System.IO;
using System.Linq;
using Nuke.Common;
using Nuke.Common.IO;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.DocFX;
using Nuke.Common.Utilities.Collections;
using static CustomTocWriter;
using static CustomDocFx;
using static Nuke.Common.IO.PathConstruction;

partial class Build
{
    AbsolutePath DocumentationRoot => RootDirectory / "docfx_project";

    AbsolutePath RepositoriesDirectory => DocumentationRoot / "repos";

    AbsolutePath GenerationDirectory => TemporaryDirectory / "packages";
    AbsolutePath ApiDirectory => DocumentationRoot / "api";

    string DocFxFile => DocumentationRoot / "docfx.json";

    IEnumerable<ApiProject> Projects =>
        SerializationTasks.YamlDeserializeFromFile<List<ApiProject>>(RootDirectory / "projects.yml");

    Target Clone => _ => _
        .Before(Restore)
        .Executes(() =>
        {
            Projects.Select(x => x.Repository)
                .ForEachLazy(x => Logger.Info($"Cloning repository '{x.HttpsUrl}'..."))
                .ForEach(x => ProcessTasks.StartProcess(
                        ToolPathResolver.GetPathExecutable("git"),
                        $"clone {x.HttpsUrl.Replace("{auth}@", string.Empty)} {RepositoriesDirectory / x.Identifier}")
                    .AssertZeroExitCode());
        });

    Target Metadata => _ => _
        .DependsOn(CustomDocFx)
        .WhenSkipped(DependencyBehavior.Skip)
        .Executes(() =>
        {
            DocFXTasks.DocFXMetadata(s => s
                .SetProjects(DocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose));
        });

    Target CustomToc => _ => _
        //.DependsOn(Restore)
        .After(Metadata)
        .Executes(() =>
        {
            GlobFiles(ApiDirectory, "**/toc.yml").ForEach(File.Delete);
            WriteCustomTocs(ApiDirectory, DocumentationRoot, GlobFiles(SourceDirectory / Configuration, "AIMP.SDK.dll"));
            //WriteCustomToc(ApiDirectory / "toc.yml", GlobFiles(RepositoriesDirectory, "**/*.sln"));
        });

    Target t => _ => _
        .Executes(() =>
        {
            WriteCustomTocs(ApiDirectory, BuildProjectDirectory, GlobFiles(GenerationDirectory, "**/lib/net4*/AIMP.SDK.dll"));
        });

    Target CustomDocFx => _ => _
        .DependsOn(Clone /*, DownloadPackages*/)
        .Executes(() =>
        {
            WriteCustomDocFx(DocFxFile, BuildProjectDirectory / "docfx.template.json", DocumentationRoot,
                ApiDirectory);
        });

    Target BuildSite => _ => _
        .DependsOn(Clean, Metadata, CustomToc)
        .Executes(() =>
        {
            DocFXTasks.DocFXBuild(s => s
                .SetConfigFile(DocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose)
                .SetServe(InvokedTargets.Contains(BuildSite)));
        });
}
