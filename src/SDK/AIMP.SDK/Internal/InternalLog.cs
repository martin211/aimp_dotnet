using System;
using System.Globalization;
using System.IO;
using System.Text;
using System.Threading;
using AIMP.SDK.Logger;

namespace AIMP.Internal
{
    /// <summary>
    /// Default SDK log sink and internal <see cref="IAimpLogger"/> implementation.
    ///
    /// It has no external dependencies and writes both to <see cref="Debug"/>
    /// (attached debugger / DebugView) and to
    /// <c>&lt;plugin&gt;\logs\YYYYMMDD.log</c>, the same file the native shim
    /// and <c>AIMP.Host.dll</c> use.
    ///
    /// The SDK uses it for its own diagnostics and for unhandled exceptions;
    /// a plugin may additionally register its own <see cref="IAimpLogger"/>.
    /// </summary>
    internal sealed class InternalLog : IAimpLogger
    {
        private const int RetentionDays = 10;

        private static readonly object Sync = new();
        private static readonly InternalLog Shared = new();

        private static string _logDirectory;

        private InternalLog()
        {
        }

        /// <summary>
        /// The logger instance the SDK uses as its internal logger.
        /// </summary>
        public static InternalLog Instance => Shared;

        /// <summary>
        /// Sets the plugin directory whose <c>logs</c> folder receives the
        /// file. Called by the host before the plugin is loaded.
        /// </summary>
        public static void Configure(string directory)
        {
            try
            {
                var logDirectory = string.IsNullOrEmpty(directory)
                    ? Path.Combine(Path.GetTempPath(), "aimp_dotnet")
                    : Path.Combine(directory, "logs");

                Directory.CreateDirectory(logDirectory);
                Cleanup(logDirectory);

                lock (Sync)
                {
                    _logDirectory = logDirectory;
                }
            }
            catch
            {
                lock (Sync)
                {
                    _logDirectory = null;
                }
            }
        }

        public void Verbose(string message)
        {
            Write("VRB", message);
        }

        public void Verbose(string message, params object[] values)
        {
            Write("VRB", message, values);
        }

        public void Verbose(Exception exception, string messageTemplate, params object[] values)
        {
            Write("VRB", exception, messageTemplate, values);
        }

        public void Information(string message)
        {
            Write("INF", message);
        }

        public void Information(string message, params object[] values)
        {
            Write("INF", message, values);
        }

        public void Information(Exception exception, string messageTemplate, params object[] values)
        {
            Write("INF", exception, messageTemplate, values);
        }

        public void Error(string message, params object[] values)
        {
            Write("ERR", message, values);
        }

        public void Error(Exception exception, string messageTemplate, params object[] values)
        {
            Write("ERR", exception, messageTemplate, values);
        }

        public void Fatal(string message)
        {
            Write("FTL", message);
        }

        public void Fatal(string message, params object[] values)
        {
            Write("FTL", message, values);
        }

        public void Fatal(Exception exception, string messageTemplate, params object[] values)
        {
            Write("FTL", exception, messageTemplate, values);
        }

        public void Debug(string message)
        {
            Write("DBG", message);
        }

        public void Debug(string message, params object[] values)
        {
            Write("DBG", message, values);
        }

        public void Debug(Exception exception, string messageTemplate, params object[] values)
        {
            Write("DBG", exception, messageTemplate, values);
        }

        private static void Write(string level, string message)
        {
            var text = Format(level, message);

            try
            {
                System.Diagnostics.Debug.WriteLine(text, "AIMP");
            }
            catch
            {
                // Debug output is optional.
            }

            Append(text);
        }

        private static void Write(string level, string messageTemplate, object[] values)
        {
            Write(level, FormatTemplate(messageTemplate, values));
        }

        private static void Write(string level, Exception exception, string messageTemplate, object[] values)
        {
            if (exception == null)
            {
                Write(level, messageTemplate, values);
                return;
            }

            var message = FormatTemplate(messageTemplate, values);
            message = string.IsNullOrEmpty(message)
                ? exception.ToString()
                : $"{message} | {exception}";

            Write(level, message);
        }

        private static void Append(string text)
        {
            try
            {
                string directory;

                lock (Sync)
                {
                    directory = _logDirectory;
                }

                if (string.IsNullOrEmpty(directory))
                {
                    return;
                }

                var path = Path.Combine(
                    directory,
                    DateTime.Now.ToString("yyyyMMdd", CultureInfo.InvariantCulture) + ".log");

                lock (Sync)
                {
                    using var stream = new FileStream(path, FileMode.Append, FileAccess.Write, FileShare.ReadWrite);
                    using var writer = new StreamWriter(stream, new UTF8Encoding(false));
                    writer.WriteLine(text);
                }
            }
            catch
            {
                // Logging must never break the plugin.
            }
        }

        private static string Format(string level, string message)
        {
            var timestamp = DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fff", CultureInfo.InvariantCulture);
            var threadId = Thread.CurrentThread.ManagedThreadId.ToString(CultureInfo.InvariantCulture);

            return $"{timestamp} [sdk] [{level}] [T{threadId}] {message ?? string.Empty}";
        }

        /// <summary>
        /// Best-effort formatting for message templates: positional
        /// placeholders are formatted, named ones are appended as values.
        /// </summary>
        private static string FormatTemplate(string template, object[] values)
        {
            if (string.IsNullOrEmpty(template))
            {
                return string.Empty;
            }

            if (values == null || values.Length == 0)
            {
                return template;
            }

            try
            {
                return string.Format(CultureInfo.InvariantCulture, template, values);
            }
            catch (FormatException)
            {
                return $"{template} {string.Join(", ", values)}";
            }
        }

        private static void Cleanup(string logDirectory)
        {
            try
            {
                var cutoff = DateTime.Now.Date.AddDays(-RetentionDays);

                foreach (var file in Directory.GetFiles(logDirectory, "*.log"))
                {
                    var name = Path.GetFileNameWithoutExtension(file);

                    if (name.Length == 8 &&
                        DateTime.TryParseExact(
                            name,
                            "yyyyMMdd",
                            CultureInfo.InvariantCulture,
                            DateTimeStyles.None,
                            out var date) &&
                        date < cutoff)
                    {
                        File.Delete(file);
                    }
                }
            }
            catch
            {
                // Retention is best-effort.
            }
        }
    }
}
