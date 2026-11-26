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
    private bool _profileCleanupScheduled;
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

#if DEBUG
// here is a stackoverflow exception in release mode. Need to rewrite the report generator.
                        var reporter = new ResultReporter(testResult, new ExtendedTextWrapper(_logWriter));
                        reporter.ReportResults();
#endif
                    }
                    catch (Exception e)
                    {
                        _logWriter.WriteLine(e.ToString());
                    }
                    finally
                    {
                        try
                        {
                            (runner as IDisposable)?.Dispose();
                        }
                        catch
                        {
                            // Ignore runner cleanup errors, the process is about to exit.
                        }

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
        try
        {
            _engine?.Dispose();
        }
        catch
        {
            // Ignore engine cleanup errors.
        }

        _engine = null;

        // Cover the case when AIMP is closed without running Terminate.
        ScheduleProfileCleanup();
    }

    /// <summary>
    /// Deletes the AIMP profile after the current process exits, so the next
    /// test run starts with a clean player. The actual deletion is performed
    /// by a detached cmd process: AIMP holds the profile while it is running.
    /// </summary>
    private void ScheduleProfileCleanup()
    {
        if (_profileCleanupScheduled)
        {
            return;
        }

        _profileCleanupScheduled = true;

        string profilePath;

        try
        {
            profilePath = Player?.Core?.GetPath(AimpCorePathType.Profile);
        }
        catch
        {
            return;
        }

        if (string.IsNullOrWhiteSpace(profilePath))
        {
            return;
        }

        profilePath = profilePath.TrimEnd('\\', '/');

        try
        {
            var arguments = "/c ping 127.0.0.1 -n 3 > nul & rmdir /s /q \"" + profilePath + "\"";
            Process.Start(new ProcessStartInfo("cmd.exe", arguments)
            {
                CreateNoWindow = true,
                UseShellExecute = false,
                WindowStyle = ProcessWindowStyle.Hidden,
                WorkingDirectory = Path.GetTempPath()
            });
        }
        catch (Exception exception)
        {
            try
            {
                _logWriter?.WriteLine("Unable to schedule profile cleanup: " + exception);
            }
            catch
            {
                // Ignore logging errors.
            }
        }
    }

    private void Terminate()
    {
        ScheduleProfileCleanup();

        try
        {
            _logWriter?.Flush();
        }
        catch
        {
            // Ignore logging errors.
        }

        try
        {
            _logWriter?.Close();
        }
        catch
        {
            // Ignore logging errors.
        }

        _logWriter = null;

        var current = Process.GetCurrentProcess();

        // Keep the original behavior: stop every running AIMP instance.
        foreach (var process in Process.GetProcessesByName("AIMP"))
        {
            try
            {
                if (process.Id == current.Id)
                {
                    continue;
                }

                process.Kill();
                process.WaitForExit();
            }
            catch
            {
                // The process may exit between enumeration and kill.
            }
            finally
            {
                process.Dispose();
            }
        }

        try
        {
            if (string.Equals(current.ProcessName, "AIMP", StringComparison.OrdinalIgnoreCase))
            {
                current.Kill();
            }
        }
        catch
        {
            Environment.Exit(0);
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
