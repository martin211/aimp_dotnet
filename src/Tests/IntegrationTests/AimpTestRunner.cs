// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2022 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Diagnostics;
using System.IO;
using AIMP;
using AIMP.SDK;
using AIMP.SDK.MessageDispatcher;
using Aimp.TestRunner.Engine;
using Aimp.TestRunner.UnitTests;
using NUnit.Engine;
using NUnit.Engine.Extensibility;
using NUnit.Engine.Services;
using NUnit.Framework;

namespace Aimp.TestRunner;

[AimpPlugin("AimpTestRunner", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons)]
public class AimpTestRunnerPlugin : AimpPlugin, ITestEventListener
{
    private readonly IResultWriter _resultWriter = new NUnit3XmlResultWriter();

    private ITestEngine _engine;
    private bool _inProgress;
    private TextWriter _logWriter;
    private string _testResultFile;

    public void OnTestEvent(string report)
    {
    }

    public override void Initialize()
    {
        var path = Path.Combine(Player.Core.GetPath(AimpCorePathType.Plugins), "AimpTestRunner");
        _logWriter = new StreamWriter(Path.Combine(path, "integration.tests.log"));

        try
        {
            AppDomain.CurrentDomain.SetData("APPBASE", path);
            Environment.CurrentDirectory = path;

            _testResultFile = Path.Combine(path, "integration.tests.xml");


            if (Player.Win32Manager.GetAimpHandle() == IntPtr.Zero)
            {
                _logWriter.WriteLine("Unable to run test. This is not AIMP.");
                _logWriter.Flush();
                _logWriter.Close();
                Terminate();
            }

            _logWriter.WriteLine($"AIMP version: {Player.ServiceVersionInfo.FormatInfo}");

            _engine = TestEngineActivator.CreateInstance();
            _engine.WorkDirectory = path;
            _engine.Initialize();
            var package = new TestPackage(Path.Combine(path, "AimpTestRunner_plugin.dll"));
            package.Settings.Add("ProcessModel", "Single");

            var runner = _engine.GetRunner(package);

            AimpTestContext.Instance.AimpPlayer = Player;

            Player.ServiceMessageDispatcher.Hook(new Hook((type, i, arg3) =>
            {
                if (type == AimpCoreMessageType.EventLoaded && !_inProgress)
                {
                    _inProgress = true;
                    try
                    {
                        _resultWriter.CheckWritability(_testResultFile);

                        var testResult = runner.Run(this, TestFilter.Empty);
                        _resultWriter.WriteResultFile(testResult, _testResultFile);
                        var reporter = new ResultReporter(testResult, new ExtendedTextWrapper(_logWriter));
                        reporter.ReportResults();
                    }
                    catch (Exception e)
                    {
                        _logWriter.WriteLine(e.ToString());
                    }
                    finally
                    {
                        _logWriter.Flush();
                        Terminate();
                    }
                }

                return new AimpActionResult(ActionResultType.OK);
            }));
        }
        catch (Exception e)
        {
            _logWriter.WriteLine(e.ToString());
            _logWriter.Flush();
            _logWriter.Close();
            Terminate();
        }
    }

    public override void Dispose()
    {
        TestContext.WriteLine("Clear local library");
        var libraryFile = Path.Combine(Player.Core.GetPath(AimpCorePathType.Audiolibrary), "Local.adb");
        if (File.Exists(libraryFile)) File.Delete(libraryFile);

        _engine = null;
    }

    private void Terminate()
    {
        _logWriter.Close();

        var processes = Process.GetProcessesByName("AIMP");

        foreach (var process in processes)
        {
            process.Kill();
            process.WaitForExit();
            process.Dispose();
        }
    }

    public class Hook : IAimpMessageHook
    {
        private readonly Func<AimpCoreMessageType, int, IntPtr, AimpActionResult> _hook;

        public Hook(Func<AimpCoreMessageType, int, IntPtr, AimpActionResult> hook)
        {
            _hook = hook;
        }

        public AimpActionResult CoreMessage(AimpCoreMessageType message, int param1, IntPtr param2)
        {
            return _hook(message, param1, param2);
        }
    }
}
