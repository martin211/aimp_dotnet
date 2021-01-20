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
using static Nuke.Common.IO.FileSystemTasks;

partial class Build
{
    AbsolutePath DocumentationRoot => RootDirectory / "docfx_project";

    AbsolutePath RepositoriesDirectory => DocumentationRoot / "repos";

    AbsolutePath GenerationDirectory => TemporaryDirectory / "packages";
    AbsolutePath ApiDirectory => DocumentationRoot / "api";

    string DocFxFile => DocumentationRoot / "docfx.json";

    IEnumerable<ApiProject> Projects =>
        SerializationTasks.YamlDeserializeFromFile<List<ApiProject>>(DocumentationRoot / "projects.yml");

    Target CleanDocumentation => _ => _
        .Executes(() =>
        {
            //SourceDirectory.GlobDirectories("**/_site").ForEach(DeleteDirectory);
        });

    Target Clone => _ => _
        .Before(Restore)
        .Executes(() =>
        {
            //Projects.Select(x => x.Repository)
            //    .ForEachLazy(x => Logger.Info($"Cloning repository '{x.HttpsUrl}'..."))
            //    .ForEach(x => ProcessTasks.StartProcess(
            //            ToolPathResolver.GetPathExecutable("git"),
            //            $"clone {x.HttpsUrl.Replace("{auth}@", string.Empty)} {RepositoriesDirectory / x.Identifier}")
            //        .AssertZeroExitCode());
        });

    Target Metadata => _ => _
        //.DependsOn(CustomDocFx)
        .WhenSkipped(DependencyBehavior.Skip)
        .Executes(() =>
        {
            DocFXTasks.DocFXMetadata(s => s
                .SetProcessWorkingDirectory(DocumentationRoot)
                .SetProjects(DocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose));
        });

    Target CustomToc => _ => _
        .After(Metadata)
        .Executes(() =>
        {
            GlobFiles(ApiDirectory, "**/toc.yml").ForEach(File.Delete);
            WriteCustomTocs(ApiDirectory, DocumentationRoot, GlobFiles(SourceDirectory / Configuration, "AIMP.SDK.dll"));
        });

    Target BuildSite => _ => _
        .DependsOn(CleanDocumentation, Metadata, CustomToc)
        .Executes(() =>
        {
            DocFXTasks.DocFXBuild(s => s
                .SetProcessWorkingDirectory(DocumentationRoot)
                .SetConfigFile(DocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose)
                .SetServe(true));
        });
}
