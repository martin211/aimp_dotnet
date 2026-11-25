using System;
using System.Diagnostics;
using System.IO;
using System.Reflection;
using AIMP.SDK;
using AIMP.SDK.Logger;

namespace AIMP.Internal
{
    /// <summary>
    /// SDK logging facade.
    ///
    /// All SDK diagnostics are routed to the logger the plugin registers
    /// (<see cref="IAimpLogger"/>). Until a logger is registered, and if a
    /// plugin does not provide one at all, messages go to
    /// <see cref="InternalLog"/> (<see cref="Debug"/>).
    /// </summary>
    internal static class AimpLog
    {
        private static readonly object Sync = new();
        private static readonly InternalLogger DefaultLogger = new();

        private static IAimpLogger _logger;
        private static IAimpLogger _bannerTarget;
        private static LoggingContext _context = LoggingContext.CreateBootstrap(null);
        private static bool _bannerPending;
        private static bool _hasPluginContext;

        /// <summary>
        /// The logger currently used by the SDK.
        /// </summary>
        public static IAimpLogger Logger
        {
            get
            {
                lock (Sync)
                {
                    return _logger ?? DefaultLogger;
                }
            }
        }

        public static void ConfigureBootstrap(string directory)
        {
            InternalLog.Configure(directory);

            lock (Sync)
            {
                _context = LoggingContext.CreateBootstrap(directory);
                _bannerPending = false;
                _hasPluginContext = false;
                _bannerTarget = null;
            }
        }

        public static void ConfigurePlugin(
            string directory,
            AimpPluginAttribute attribute,
            AimpPlugin plugin)
        {
            InternalLog.Configure(directory);

            lock (Sync)
            {
                _context = LoggingContext.CreatePlugin(directory, attribute, plugin);
                _bannerPending = true;
                _hasPluginContext = true;
                _bannerTarget = null;
            }
        }

        /// <summary>
        /// Registers the plugin logger. The plugin/SDK/host version banner is
        /// written to it, including when the plugin replaces the default
        /// logger from <see cref="AimpPlugin.Initialize"/>.
        /// Passing <c>null</c> restores the default debug logger.
        /// </summary>
        public static void Register(IAimpLogger logger)
        {
            LoggingContext context;
            bool writeBanner;

            lock (Sync)
            {
                _logger = logger;
                context = _context;
                writeBanner = logger != null &&
                              (_bannerPending ||
                               (_hasPluginContext && !ReferenceEquals(_bannerTarget, logger)));

                _bannerPending = false;

                if (writeBanner)
                {
                    _bannerTarget = logger;
                }
            }

            if (writeBanner)
            {
                WriteBanner(context);
            }
        }

        public static void Write(string message)
        {
            // The SDK always keeps its own log file, even when a plugin has
            // registered a custom logger that only forwards to a debugger.
            InternalLog.Instance.Information(message);

            var logger = _logger;

            if (logger == null || logger is InternalLogger)
            {
                return;
            }

            try
            {
                logger.Information(message);
            }
            catch (Exception exception)
            {
                InternalLog.Instance.Error(
                    exception,
                    "Registered logger failed, message was: {Message}",
                    message);
            }
        }

        public static void Write(Exception exception)
        {
            if (exception == null)
            {
                InternalLog.Instance.Error("Unhandled exception: <null>");
                return;
            }

            InternalLog.Instance.Error(exception, "Unhandled exception");

            var logger = _logger;

            if (logger == null || logger is InternalLogger)
            {
                return;
            }

            try
            {
                logger.Error(exception, "Unhandled exception");
            }
            catch (Exception loggingException)
            {
                InternalLog.Instance.Error(
                    loggingException,
                    "Registered logger failed while handling an exception: {Exception}",
                    exception);
            }
        }

        /// <summary>
        /// Drops the registered logger; used when the AppDomain unloads.
        /// </summary>
        public static void Close()
        {
            lock (Sync)
            {
                _logger = null;
                _bannerPending = false;
                _bannerTarget = null;
                _hasPluginContext = false;
            }
        }

        private static void WriteBanner(LoggingContext context)
        {
            Write($"AIMP managed plugin: {context.PluginName} {context.PluginVersion} by {context.PluginAuthor}");
            Write($"AIMP.SDK: {context.SdkVersion}");
            Write($"AIMP.Host: {context.HostVersion}");
            Write($"Native shim: {context.ShimVersion}");
            Write($"Plugin assembly: {context.PluginAssembly} ({context.PluginAssemblyVersion})");
            Write($"Process: {context.Bitness}, CLR {context.Framework}, {context.OsVersion}, machine {context.MachineName}, pid {context.ProcessId}");
        }

        private sealed class LoggingContext
        {
            public string PluginName;
            public string PluginVersion;
            public string PluginAuthor;
            public string PluginAssembly;
            public string PluginAssemblyVersion;
            public string SdkVersion;
            public string HostVersion;
            public string ShimVersion;
            public string Bitness;
            public string Framework;
            public string OsVersion;
            public string MachineName;
            public int ProcessId;

            public static LoggingContext CreateBootstrap(string directory)
            {
                var context = CreateBase(directory);

                context.PluginName = "bootstrap";
                context.PluginVersion = "-";
                context.PluginAuthor = "-";
                context.PluginAssembly = "-";
                context.PluginAssemblyVersion = "-";

                return context;
            }

            public static LoggingContext CreatePlugin(
                string directory,
                AimpPluginAttribute attribute,
                AimpPlugin plugin)
            {
                var context = CreateBase(directory);
                var pluginType = plugin.GetType();
                var pluginAssembly = pluginType.Assembly;

                context.PluginName = attribute?.Name ?? pluginType.Name;
                context.PluginVersion = attribute?.Version ?? "-";
                context.PluginAuthor = string.IsNullOrEmpty(attribute?.Author) ? "-" : attribute.Author;
                context.PluginAssembly = pluginAssembly.Location;
                context.PluginAssemblyVersion = pluginAssembly.GetName().Version?.ToString() ?? "-";

                return context;
            }

            private static LoggingContext CreateBase(string directory)
            {
                return new LoggingContext
                {
                    SdkVersion = GetAssemblyVersion(typeof(AimpLog).Assembly),
                    HostVersion = GetFileVersion(directory, "AIMP.Host.dll"),
                    ShimVersion = GetShimVersion(directory),
                    Bitness = Environment.Is64BitProcess ? "x64" : "x86",
                    Framework = Environment.Version.ToString(),
                    OsVersion = Environment.OSVersion.ToString(),
                    MachineName = Environment.MachineName,
                    ProcessId = GetProcessId()
                };
            }

            private static string GetShimVersion(string directory)
            {
                if (string.IsNullOrEmpty(directory))
                {
                    return "-";
                }

                var folderName = new DirectoryInfo(directory).Name;
                var candidates = new[]
                {
                    folderName + ".dll",
                    "aimp_dotnet.dll",
                    "aimp_managed.dll"
                };

                foreach (var candidate in candidates)
                {
                    var value = GetFileVersion(directory, candidate);
                    if (value != "-")
                    {
                        return value;
                    }
                }

                return "-";
            }

            private static string GetFileVersion(string directory, string fileName)
            {
                if (string.IsNullOrEmpty(directory) || string.IsNullOrEmpty(fileName))
                {
                    return "-";
                }

                try
                {
                    var path = Path.Combine(directory, fileName);

                    if (!File.Exists(path))
                    {
                        return "-";
                    }

                    var version = FileVersionInfo.GetVersionInfo(path);
                    return string.IsNullOrEmpty(version.FileVersion)
                        ? version.ProductVersion ?? "-"
                        : version.FileVersion;
                }
                catch
                {
                    return "-";
                }
            }

            private static string GetAssemblyVersion(Assembly assembly)
            {
                try
                {
                    var version = assembly.GetName().Version?.ToString() ?? "-";
                    var informational = assembly
                        .GetCustomAttribute<AssemblyInformationalVersionAttribute>()
                        ?.InformationalVersion;

                    return string.IsNullOrEmpty(informational) || informational == version
                        ? version
                        : $"{version} ({informational})";
                }
                catch
                {
                    return "-";
                }
            }

            private static int GetProcessId()
            {
                try
                {
                    return Process.GetCurrentProcess().Id;
                }
                catch
                {
                    return 0;
                }
            }
        }
    }
}