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
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.XPath;
using System.Xml.Xsl;
using DefaultNamespace;
using Nuke.Common;
using Nuke.Common.CI.TeamCity;
using Nuke.Common.IO;
using Nuke.Common.Tooling;
using Nuke.Common.Utilities.Collections;
using static Nuke.Common.IO.FileSystemTasks;
using Serilog;

partial class Build
{
    AbsolutePath ResourcesPath => SourceDirectory / "Tests" / "Resources";
    AbsolutePath TestOutput => RootDirectory / "Tests";

    [Parameter(Name = "AimpPath")] readonly string IntegrationTestAimpPath = @"z:\code\aimp\AIMP5.00.2344\";
    [Parameter(Name = "TimeOut")] readonly int IntegrationTestTimeout = 5; // 5 minutes
    [Parameter(Name = "IsJUnit")] readonly bool IntegrationTestIsJUnit;
    [Parameter(Name = "TestResultPath")] string IntegrationTestTestResultPath;
    [Parameter(Name = "Platform")] string IntegrationTestTestPlatform = "x86";

    AbsolutePath IntegrationTestBinPath => SourceDirectory / "Tests" / "IntegrationTests";
    AbsolutePath IntegrationTestPluginPath => (AbsolutePath) Path.Combine(IntegrationTestAimpPath, "Plugins", "AimpTestRunner");
    AbsolutePath IntegrationTestOutput => (AbsolutePath) Path.Combine(@"c:\tmp\aimp\sdk\tests\");
    Target PrepareTestConfiguration => _ => _
        .Executes(() =>
        {
            var outPath = Configuration == Configuration.Release ? IntegrationTestOutput : TestOutput;

            Log.Debug("Preparing test settings");
            DeleteDirectory(outPath);
            EnsureCleanDirectory(outPath);
            Directory.CreateDirectory(outPath);

            var setting = new DefaultSettings();
            setting.Default = new GhprSettings
            {
                OutputPath = outPath,
                DataServiceFile = "Ghpr.LocalFileSystem.dll",
                ReportName = "AIMP SDK Test Result",
                ProjectName = "AIMP DotNet SDK",
                LoggerFile = "",
                Sprint = GitRepository.Branch,
                RunName = "",
                RunGuid = "",
                RealTimeGeneration = "True",
                RunsToDisplay = "5",
                TestsToDisplay = "5",
                EscapeTestOutput = true,
                Retention = new Retention
                {
                    Amount = 1000
                }
            };

            setting.Projects = new List<Project>();
            var settingContent = SerializationTasks.JsonSerialize(setting);

            Log.Debug(settingContent);

            File.WriteAllText(IntegrationTestPluginPath / "Ghpr.NUnit.Settings.json", settingContent);
        });

    Target PrepareIntegrationTests => _ => _
        .Requires(() => IntegrationTestAimpPath, () => IntegrationTestTestPlatform)
        .Executes(() =>
        {
            DeleteDirectory(IntegrationTestPluginPath);
            EnsureCleanDirectory(IntegrationTestPluginPath);

            Directory.CreateDirectory(IntegrationTestPluginPath);
            EnsureExistingDirectory(IntegrationTestPluginPath);

            var testBinPath = IntegrationTestBinPath;
            var testPattern = $"**/bin/{IntegrationTestTestPlatform}/{Configuration}";

            Log.Information("Test bin files path: '{testBinPath}'", testBinPath);
            Log.Information($"Test bin files path: '{testBinPath}'");
            Log.Information($"Search pattern: {testPattern}");

            void copyFilesFromFolder(string folder)
            {
                Log.Debug($"Copy plugin files from '{folder}' to '{IntegrationTestPluginPath}'");
                var files = Directory.GetFiles(folder, "*.dll");
                foreach (var file in files)
                {
                    if (file.EndsWith("aimp_dotnet.dll"))
                    {
                        //CopyFile(file, IntegrationTestPluginPath / "AimpTestRunner.dll");
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

                Directory.GetFiles(folder, "*.pdb")
                    .NotNull()
                    .ForEach(file =>
                    {
                        if (file.EndsWith("AimpTestRunner.pdb"))
                        {
                            CopyFile(file, IntegrationTestPluginPath / "AimpTestRunner_plugin.pdb");
                        }
                        else
                        {
                            CopyFileToDirectory(file, IntegrationTestPluginPath);
                        }
                    });
            }

            testBinPath.GlobDirectories($"**/bin/{IntegrationTestTestPlatform}/{Configuration}").ForEach(d =>
            {
                copyFilesFromFolder(d);
                Log.Debug($"Copy {d}/nunit.engine.addins to {IntegrationTestPluginPath}");
                CopyFileToDirectory(d / "nunit.engine.addins", IntegrationTestPluginPath);
            });

            var sdkFolder = new DirectoryInfo(SDKBinFolder / $"{IntegrationTestTestPlatform}/{Configuration}");
            var sdkFiles = sdkFolder.GetFiles("*.dll");
            foreach (var file in sdkFiles)
            {
                if (file.FullName.EndsWith("aimp_dotnet.dll"))
                {
                    file.CopyTo(IntegrationTestPluginPath / "AimpTestRunner.dll", true);
                }
            }

            CopyDirectoryRecursively(ResourcesPath / "integrationTests", IntegrationTestPluginPath / "Resources");
        });

    Target ExecuteIntegrationTests => _ => _
        .Requires(() => IntegrationTestAimpPath)
        .DependsOn(PrintBuildParameters, PrepareIntegrationTests, PrepareTestConfiguration)
        .Executes(() =>
        {
            var testResultFile = IntegrationTestPluginPath / "integration.tests.xml";
            var testResultLogFile = IntegrationTestPluginPath / "integration.tests.log";

            if (File.Exists(testResultFile))
                File.Delete(testResultFile);

            if (File.Exists(testResultLogFile))
                File.Delete(testResultLogFile);

            var aimpExe = Path.Combine(IntegrationTestAimpPath, "AIMP.exe");
            if (!File.Exists(aimpExe))
            {
                LogError($"AIMP.exe not found at path {aimpExe}");
                TeamCity.Instance?.WriteFailure($"AIMP.exe not found at path {aimpExe}");
                Assert.Fail("Unable to run test.");
                return;
            }

            Log.Information("Start AIMP process");
            var p = ProcessTasks.StartProcess(aimpExe, "/DEBUG", IntegrationTestAimpPath, timeout: IntegrationTestTimeout * 60000);
            var res = p.WaitForExit();

            if (res)
            {
                if (!File.Exists(testResultFile) || !File.Exists(testResultLogFile) || new FileInfo(testResultLogFile).Length == 0)
                {
                    LogError("Unable to run integration tests.");
                    TeamCity.Instance?.WriteFailure($"Unable to run integration tests. {testResultFile} NOT FOUND");
                    Assert.Fail("Unable to run test.");
                }
                else
                {
                    var isValid = true;

                    CopyFileToDirectory(testResultFile, OutputDirectory, FileExistsPolicy.Overwrite);
                    CopyFileToDirectory(testResultLogFile, OutputDirectory, FileExistsPolicy.Overwrite);

                    var content = File.ReadAllText(testResultLogFile);
                    var r = new Regex(@"Failed:\s(\d*)");
                    var matches = r.Matches(content);

                    if (matches.Count > 0 && matches[0].Groups.Count >= 1)
                    {
                        if (int.TryParse(matches[0].Groups[1].Value, out var failed))
                        {
                            if (failed > 0)
                            {
                                isValid = false;
                            }
                        }
                    }

                    Log.Debug(content);

                    if (IntegrationTestIsJUnit)
                    {
                        var junitReport = OutputDirectory / "junit-integration.tests.xml";

                        var xslt = new XslTransform();
                        xslt.Load(RootDirectory / "nunit3-junit.xslt");
                        var doc = new XPathDocument(testResultFile);
                        using var writer = new XmlTextWriter(junitReport, Encoding.UTF8)
                        {
                            Formatting = Formatting.Indented
                        };
                        xslt.Transform(doc, null, writer, null);
                    }

                    if (!isValid)
                    {
                        Assert.Fail("Test is failed.");
                    }
                }
            }
            else
            {
                Log.Fatal("Process was ended by timeout. Try to increase `TestTimeout` parameter. Check logs. Check that plugin was activated at AIMP settings.");
                Assert.Fail("Unable to run test.");
            }
        });

    Target CopyTestResults => _ => _
        .Requires(() => IntegrationTestTestResultPath)
        .Executes(() =>
        {
            Log.Information("Copy test results from {from} to {to}", IntegrationTestOutput, IntegrationTestTestResultPath);
            CopyDirectoryRecursively(IntegrationTestOutput, IntegrationTestTestResultPath, DirectoryExistsPolicy.Merge, FileExistsPolicy.OverwriteIfNewer);
        });

    void LogError(string message)
    {
        Log.Error(message);
    }
}
