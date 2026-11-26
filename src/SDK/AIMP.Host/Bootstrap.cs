using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;

namespace AIMP.Host
{
    /// <summary>
    /// Stable loader between the native shim and the per-plugin
    /// <c>AIMP.SDK.dll</c>.
    ///
    /// The native shim loads <c>AIMP.Host.dll</c> into the default AppDomain.
    /// This assembly never changes its ABI, so each plugin folder may carry a
    /// different <c>AIMP.SDK.dll</c> version: the host creates a dedicated
    /// <see cref="AppDomain"/>, loads the SDK from that folder and invokes its
    /// bootstrap through reflection.
    /// </summary>
    public static class Bootstrap
    {
        private const string SdkAssemblyName = "AIMP.SDK.dll";
        private const string SdkTypeName = "AIMP.Loader.Bootstrap";
        private const string SdkMethodName = "StartPlugin";

        private static readonly List<AppDomain> Domains = new();
        private static readonly object Sync = new();

        /// <summary>
        /// Argument format: <c>&lt;host directory&gt;|&lt;shim module handle&gt;</c>.
        /// </summary>
        public static int Start(string argument)
        {
            var separator = argument?.LastIndexOf('|') ?? -1;
            if (separator <= 0)
            {
                return 2;
            }

            var directory = argument.Substring(0, separator);
            var module = argument.Substring(separator + 1);

            AppDomain aimpDomain = null;

            WriteLog(directory, $"AIMP.Host {GetHostVersion()} | {(Environment.Is64BitProcess ? "x64" : "x86")} | CLR {Environment.Version}");

            try
            {
                var domainSetup = new AppDomainSetup
                {
                    ApplicationBase = directory,
                    ApplicationName = Path.GetFileName(directory.TrimEnd('\\', '/'))
                };

                aimpDomain = AppDomain.CreateDomain(
                    "AIMP.Plugin." + domainSetup.ApplicationName + "." + Guid.NewGuid().ToString("N"),
                    null,
                    domainSetup);

                aimpDomain.SetData("aimp.directory", directory);
                aimpDomain.SetData("aimp.module", module);
                aimpDomain.SetData("aimp.result", 1);

                aimpDomain.DoCallBack(StartInDomain);

                var result = aimpDomain.GetData("aimp.result") is int code ? code : 1;

                if (result == 0)
                {
                    lock (Sync)
                    {
                        Domains.Add(aimpDomain);
                    }

                    return 0;
                }

                var error = aimpDomain.GetData("aimp.error") as string;
                if (!string.IsNullOrEmpty(error))
                {
                    WriteLog(directory, error);
                }

                WriteLog(directory, "AIMP.Host: plugin domain failed to start.");
            }
            catch (Exception exception)
            {
                WriteLog(directory, exception.ToString());
            }

            if (aimpDomain != null)
            {
                AppDomain.Unload(aimpDomain);
            }

            return 1;
        }

        private static void StartInDomain()
        {
            var domain = AppDomain.CurrentDomain;
            var directory = (string)domain.GetData("aimp.directory");
            var module = (string)domain.GetData("aimp.module");

            try
            {
                AppDomain.CurrentDomain.AssemblyResolve += OnAssemblyResolve;

                var sdkPath = Path.Combine(directory, SdkAssemblyName);
                WriteLog(directory, $"loading {sdkPath}");

                var assembly = Assembly.LoadFrom(sdkPath);
                var type = assembly.GetType(SdkTypeName, true);

                var method = type.GetMethod(
                    SdkMethodName,
                    BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);

                if (method == null)
                {
                    throw new MissingMethodException(SdkTypeName, SdkMethodName);
                }

                var result = method.Invoke(null, new object[] { directory, module }) is int code ? code : 1;
                domain.SetData("aimp.result", result);
            }
            catch (Exception exception)
            {
                domain.SetData("aimp.error", exception.ToString());
                WriteLog(directory, exception.ToString());
                domain.SetData("aimp.result", 1);
            }
        }

        private static Assembly OnAssemblyResolve(object sender, ResolveEventArgs args)
        {
            try
            {
                var directory = (string)AppDomain.CurrentDomain.GetData("aimp.directory");
                if (string.IsNullOrEmpty(directory))
                {
                    return null;
                }

                var name = new AssemblyName(args.Name).Name;
                var path = Path.Combine(directory, name + ".dll");

                return File.Exists(path) ? Assembly.LoadFrom(path) : null;
            }
            catch
            {
                return null;
            }
        }

        private static void WriteLog(string directory, string message)
        {
            try
            {
                var logDirectory = Path.Combine(directory, "logs");
                Directory.CreateDirectory(logDirectory);
                var logFile = Path.Combine(logDirectory, DateTime.Now.ToString("yyyyMMdd") + ".log");
                var logRow =
                    $"{DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff")} [host {GetHostVersion()}] [environment {(Environment.Is64BitProcess ? "x64" : "x86")}] [thread {System.Threading.Thread.CurrentThread.ManagedThreadId}] [message {message}]"; 

                using var stream = new FileStream(logFile, FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
                using var writer = new StreamWriter(stream, new System.Text.UTF8Encoding(false));
                writer.WriteLine(logRow);
            }
            catch
            {
                // Logging must never break the bootstrap.
            }
        }

        private static string GetHostVersion()
        {
            return typeof(Bootstrap).Assembly.GetName().Version?.ToString() ?? "-";
        }
    }
}
