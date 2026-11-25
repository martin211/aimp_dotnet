using System;
using System.Runtime.InteropServices;

namespace AIMP.Loader
{
    /// <summary>
    /// Calls back into the native shim that started us.
    /// </summary>
    internal static class ShimBridge
    {
        [DllImport("kernel32", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        private static extern IntPtr GetProcAddress(IntPtr module, string procedureName);

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        private delegate void SetPluginCallback(IntPtr plugin);

        public static void SetPlugin(IntPtr module, IntPtr plugin)
        {
            var address = GetProcAddress(module, "AimpShimSetPlugin");
            if (address == IntPtr.Zero)
            {
                throw new EntryPointNotFoundException("AimpShimSetPlugin was not found in the native shim module.");
            }

            var callback = (SetPluginCallback)Marshal.GetDelegateForFunctionPointer(address, typeof(SetPluginCallback));

            callback(plugin);
        }
    }
}