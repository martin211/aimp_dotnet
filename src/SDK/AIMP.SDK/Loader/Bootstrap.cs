using System;
using System.Runtime.InteropServices;
using System.Threading.Tasks;
using AIMP.Internal;
using AIMP.Internal.Native.Plugin;

namespace AIMP.Loader
{
    /// <summary>
    /// Per-plugin entry point. It is invoked by <c>AIMP.Host.dll</c> inside the
    /// dedicated <see cref="AppDomain"/> created for the plugin folder.
    /// </summary>
    public static class Bootstrap
    {
        private static bool _handlersAttached;

        /// <summary>
        /// Legacy entry point. Older shims call <c>Bootstrap.Start</c> directly;
        /// new shims go through <c>AIMP.Host.dll</c> and
        /// <see cref="StartPlugin"/>.
        /// Argument format: <c>&lt;host directory&gt;|&lt;shim module handle&gt;</c>.
        /// </summary>
        public static int Start(string argument)
        {
            var separator = argument?.LastIndexOf('|') ?? -1;
            if (separator <= 0)
            {
                return 2;
            }

            return StartPlugin(
                argument.Substring(0, separator),
                argument.Substring(separator + 1));
        }

        /// <summary>
        /// Loads the plugin from <paramref name="directory"/> and hands its CCW
        /// back to the native shim identified by <paramref name="moduleText"/>.
        /// </summary>
        public static int StartPlugin(string directory, string moduleText)
        {
            try
            {
                var module = new IntPtr((long)ulong.Parse(moduleText));

                AimpLog.ConfigureBootstrap(directory);
                AttachExceptionHandlers();
                AimpLog.Write($"Bootstrap: host directory '{directory}'");

                var plugin = PluginHost.Load(directory);
                AimpLog.ConfigurePlugin(directory, plugin.Attribute, plugin.Plugin);

                var bridge = new NativePluginBridge(plugin.Plugin, plugin.Attribute);

                var pointer = Marshal.GetComInterfaceForObject(bridge, typeof(IAimpPluginNative));
                ShimBridge.SetPlugin(module, pointer);

                AimpLog.Write($"Plugin '{plugin.Attribute.Name}' handed over to AIMP");
                return 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 1;
            }
        }

        private static void AttachExceptionHandlers()
        {
            if (_handlersAttached)
            {
                return;
            }

            _handlersAttached = true;

            AppDomain.CurrentDomain.UnhandledException += OnUnhandledException;
            TaskScheduler.UnobservedTaskException += OnUnobservedTaskException;
        }

        private static void OnUnhandledException(object sender, UnhandledExceptionEventArgs e)
        {
            var exception = e.ExceptionObject as Exception;

            if (exception != null)
            {
                AimpLog.Write(exception);
                return;
            }

            AimpLog.Write($"Unhandled exception: {e.ExceptionObject}");
        }

        private static void OnUnobservedTaskException(object sender, UnobservedTaskExceptionEventArgs e)
        {
            AimpLog.Write(e.Exception);
            e.SetObserved();
        }
    }
}