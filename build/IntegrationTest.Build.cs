using System;
using System.IO;
using DefaultNamespace;
using Newtonsoft.Json;
using Nuke.Common;
using Nuke.Common.IO;
using Nuke.Common.Tooling;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.IO.FileSystemTasks;

partial class Build
{
    AbsolutePath ResourcesPath => RootDirectory / "resources";
    AbsolutePath IntegrationTestPath => RootDirectory / ".integrationTests";
    AbsolutePath IntegrationTestPluginPath => SourceDirectory / "IntegrationTest";
    AbsolutePath IntegrationPluginFolder => IntegrationTestPath / "aimp" / "plugins" / "AimpTestRunner";

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
            File.WriteAllText(IntegrationPluginFolder / "Ghpr.NUnit.Settings.json", settingContent);
        });

    Target PrepareIntegrationTests => _ => _
        .Executes(() =>
        {
            DeleteDirectory(IntegrationTestPath);
            EnsureCleanDirectory(IntegrationTestPath);

            Directory.CreateDirectory(IntegrationTestPath);
            EnsureExistingDirectory(IntegrationTestPath);

            var aimpZip = ResourcesPath / "AIMP4.60.2180.zip";
            CompressionTasks.Uncompress(aimpZip, IntegrationTestPath / "aimp");
            Directory.CreateDirectory(IntegrationPluginFolder);

            IntegrationTestPluginPath.GlobDirectories($"**/bin/{Configuration}").ForEach(d =>
            {
                var files = Directory.GetFiles(d, "*.dll");
                foreach (var file in files)
                {
                    if (file.EndsWith("aimp_dotnet.dll"))
                    {
                        CopyFile(file, IntegrationPluginFolder / "AimpTestRunner.dll");
                    }
                    else if (file.EndsWith("AimpTestRunner.dll"))
                    {
                        CopyFile(file, IntegrationPluginFolder / "AimpTestRunner_plugin.dll");
                    }
                    else
                    {
                        CopyFileToDirectory(file, IntegrationPluginFolder);
                    }
                }

                CopyFileToDirectory(d / "nunit.engine.addins", IntegrationPluginFolder);
            });

            CopyDirectoryRecursively(ResourcesPath / "integrationTests", IntegrationPluginFolder / "resources");
        });

    Target ExecuteIntegrationTests => _ => _
        .DependsOn(PrepareIntegrationTests, PrepareTestConfiguration)
        .Executes(() =>
        {
            ProcessTasks.StartProcess(IntegrationTestPath / "aimp" / "AIMP.exe", "/DEBUG", IntegrationTestPath / "aimp");
        });
}
