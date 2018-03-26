using System;
using System.IO;
using System.Linq;
using Nuke.Common;
using Nuke.Common.Git;
using Nuke.Common.Tools.GitVersion;
using Nuke.Common.Tools.MSBuild;
using Nuke.Common.Tools.NuGet;
using Nuke.Core;
using Nuke.Core.Tooling;
using static Nuke.Common.Tools.MSBuild.MSBuildTasks;
using static Nuke.Core.IO.FileSystemTasks;
using static Nuke.Core.IO.PathConstruction;
using static Nuke.Core.EnvironmentInfo;

class Build : NukeBuild
{
    // Console application entry. Also defines the default target.
    public static int Main () => Execute<Build>(x => x.Pack);

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
            // .DependsOn(Restore)
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
                var fileContent = File.ReadAllText(rcFile);
                fileContent = fileContent.Replace("1,0,0,1", GitVersion.AssemblySemVer).Replace("1.0.0.1", GitVersion.AssemblySemVer);
                File.WriteAllText(rcFile, fileContent);
            }
        });

    Target Pack => _ => _
        .Executes(() =>
        {
            NuGetTasks.NuGetPack();
        });
}
