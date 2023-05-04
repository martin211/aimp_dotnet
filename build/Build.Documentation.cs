//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using System.IO;
using Nuke.Common;
using Nuke.Common.IO;
using Nuke.Common.Tooling;
using Nuke.Common.Tools.DocFX;
using Nuke.Common.Utilities.Collections;
using Serilog;
using static CustomTocWriter;
using static Nuke.Common.IO.PathConstruction;
using static Nuke.Common.IO.FileSystemTasks;

partial class Build
{
    [Parameter] string DocumentationOutputPath;
    [Parameter] string DocumentationRepositoryUrl;

    AbsolutePath DocumentationRoot => RootDirectory / "docfx_project";
    AbsolutePath DocumentationRepositoriesDirectory => DocumentationRoot / "repos";
    AbsolutePath DocumentationApiDirectory => DocumentationRoot / "api";
    AbsolutePath DocumentationBuildOutput => RootDirectory / "_site";
    string DocumentationDocFxFile => DocumentationRoot / "docfx.json";

    IEnumerable<ApiProject> Projects =>
        SerializationTasks.YamlDeserializeFromFile<List<ApiProject>>(DocumentationRoot / "projects.yml");

    Target CleanDocumentation => _ => _
        .Executes(() =>
        {
            //SourceDirectory.GlobDirectories("**/_site").ForEach(DeleteDirectory);
        });

    Target Metadata => _ => _
        //.DependsOn(CustomDocFx)
        .WhenSkipped(DependencyBehavior.Skip)
        .Executes(() =>
        {
            DocFXTasks.DocFXMetadata(s => s
                .SetProcessWorkingDirectory(DocumentationRoot)
                .SetProjects(DocumentationDocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose));
        });

    Target CustomToc => _ => _
        .After(Metadata)
        .Executes(() =>
        {
            GlobFiles(DocumentationApiDirectory, "**/toc.yml").ForEach(File.Delete);
            WriteCustomTocs(DocumentationApiDirectory, DocumentationRoot, GlobFiles(SDKBinFolder / "x86" / GetConfiguration(), "AIMP.SDK.dll"));
        });

    Target BuildDocumentation => _ => _
        .DependsOn(CleanDocumentation, Metadata, CustomToc)
        .Executes(() =>
        {
            PrintParameters("Documentation");

            DocFXTasks.DocFXBuild(s => s
                .SetProcessWorkingDirectory(DocumentationRoot)
                .SetConfigFile(DocumentationDocFxFile)
                .SetLogLevel(DocFXLogLevel.Verbose)
                .SetServe(false));
        });

    Target PublishDocumentation => _ => _
        .Requires(() => DocumentationOutputPath)
        .Executes(() =>
        {
            CopyDirectoryRecursively(DocumentationBuildOutput, DocumentationOutputPath, DirectoryExistsPolicy.Merge, FileExistsPolicy.OverwriteIfNewer);
        });

    Target PushDocumentation => _ => _
        .Requires(() => DocumentationRepositoryUrl)
        .Executes(() =>
        {
            Log.Information("Cloning documentation repository {repository} to {output}", DocumentationRepositoryUrl, DocumentationRepositoriesDirectory);

            ProcessTasks.StartProcess(
                ToolPathResolver.GetPathExecutable("git"),
                $"clone {DocumentationRepositoryUrl.Replace("{auth}@", string.Empty)} {DocumentationRepositoriesDirectory}")
                .AssertZeroExitCode();
        }, () =>
        {
            Log.Information("Copy new documentation to repository");
            CopyDirectoryRecursively(DocumentationBuildOutput, DocumentationRepositoriesDirectory, DirectoryExistsPolicy.Merge, FileExistsPolicy.Overwrite);
        });
}
