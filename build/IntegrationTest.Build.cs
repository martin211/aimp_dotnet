using System.IO;
using DefaultNamespace;
using Nuke.Common;
using Nuke.Common.IO;
using Nuke.Common.Tooling;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.IO.FileSystemTasks;

partial class Build
{
    AbsolutePath ResourcesPath => RootDirectory / "resources";
    [Parameter] readonly string AimpPath;

    AbsolutePath IntegrationTestBinPath => SourceDirectory / "IntegrationTest";
    AbsolutePath IntegrationTestPluginPath => (AbsolutePath) Path.Combine(AimpPath, "plugins", "AimpTestRunner");

    Target PrepareTestConfiguration => _ => _
        .Executes(() =>
        {
            var setting = new DefaultSettings();
            setting.Default = new GhprSettings
            {
                OutputPath = TestOutput,
                DataServiceFile = "Ghpr.LocalFileSystem.dll",
                ReportName = "AIMP SDK Test Result",
                ProjectName = "AIMP DotNet SDK"
            };

            var settingContent = SerializationTasks.JsonSerialize(setting);
            File.WriteAllText(IntegrationTestPluginPath / "Ghpr.NUnit.Settings.json", settingContent);
        });

    Target PrepareIntegrationTests => _ => _
        .Requires(() => AimpPath)
        .Executes(() =>
        {
            DeleteDirectory(IntegrationTestPluginPath);
            EnsureCleanDirectory(IntegrationTestPluginPath);

            Directory.CreateDirectory(IntegrationTestPluginPath);
            EnsureExistingDirectory(IntegrationTestPluginPath);

            IntegrationTestBinPath.GlobDirectories($"**/bin/{Configuration}").ForEach(d =>
            {
                var files = Directory.GetFiles(d, "*.dll");
                foreach (var file in files)
                {
                    if (file.EndsWith("aimp_dotnet.dll"))
                    {
                        CopyFile(file, IntegrationTestPluginPath / "AimpTestRunner.dll");
                    }
                    else if (file.EndsWith("AimpTestRunner.dll"))
                    {
                        CopyFile(file, IntegrationTestPluginPath / "AimpTestRunner_plugin.dll");
                    }
                    else
                    {
                        CopyFileToDirectory(file, IntegrationTestPluginPath);
                    }
                }

                CopyFileToDirectory(d / "nunit.engine.addins", IntegrationTestPluginPath);
            });

            CopyDirectoryRecursively(ResourcesPath / "integrationTests", IntegrationTestPluginPath / "resources");
        });

    Target ExecuteIntegrationTests => _ => _
        .Requires(() => AimpPath)
        .DependsOn(PrepareIntegrationTests, PrepareTestConfiguration)
        .Executes(() =>
        {
            ProcessTasks.StartProcess(Path.Combine(AimpPath, "AIMP.exe"), "/DEBUG", AimpPath);
            CopyFileToDirectory(IntegrationTestPluginPath / "integration.tests.xml", OutputDirectory);
            CopyFileToDirectory(IntegrationTestPluginPath / "integration.tests.log", OutputDirectory);
        });
}
