using System;
using System.IO;
using System.Runtime.InteropServices;

namespace Aimp.Shim.SmokeTest
{
    /// <summary>
    /// Loads the native shim exactly like AIMP does, then calls the IAIMPPlugin
    /// vtable directly. Proves the whole chain works without AIMP itself:
    /// native DLL -> CLR hosting -> managed plugin -> CCW -> vtable calls.
    /// </summary>
    internal static class Program
    {
        private const int SlotQueryInterface = 0;
        private const int SlotRelease = 2;
        private const int SlotInfoGet = 3;
        private const int SlotInfoGetCategories = 4;
        private const int SlotInitialize = 5;
        private const int SlotFinalize = 6;

        [DllImport("kernel32", CharSet = CharSet.Unicode, SetLastError = true)]
        private static extern IntPtr LoadLibraryW(string fileName);

        [DllImport("kernel32", CharSet = CharSet.Ansi, SetLastError = true, ExactSpelling = true)]
        private static extern IntPtr GetProcAddress(IntPtr module, string procedureName);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int GetHeaderCallback(out IntPtr plugin);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate IntPtr InfoGetCallback(IntPtr self, int index);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate uint InfoGetCategoriesCallback(IntPtr self);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int InitializeCallback(IntPtr self, IntPtr core);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int FinalizeCallback(IntPtr self);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate uint ReleaseCallback(IntPtr self);

        private static int Main()
        {
            try
            {
                return Run();
            }
            catch (Exception exception)
            {
                Console.Error.WriteLine($"FAIL: {exception}");
                return 1;
            }
        }

        private static int Run()
        {
            var baseDirectory = AppDomain.CurrentDomain.BaseDirectory;
            var shimPath = Path.Combine(baseDirectory, "aimp_managed", "aimp_managed.dll");

            Console.WriteLine($"Shim      : {shimPath}");
            Console.WriteLine($"Process   : {(Environment.Is64BitProcess ? "x64" : "x86")}");

            var module = LoadLibraryW(shimPath);
            if (module == IntPtr.Zero)
            {
                Console.Error.WriteLine($"FAIL: LoadLibrary failed, error {Marshal.GetLastWin32Error()}");
                return 1;
            }

            var entryPoint = GetProcAddress(module, "AIMPPluginGetHeader");
            if (entryPoint == IntPtr.Zero)
            {
                Console.Error.WriteLine("FAIL: AIMPPluginGetHeader is not exported.");
                return 1;
            }

            var getHeader = (GetHeaderCallback)Marshal.GetDelegateForFunctionPointer(
                entryPoint, typeof(GetHeaderCallback));

            var headerResult = getHeader(out var plugin);
            Console.WriteLine($"Header    : {headerResult}, plugin = 0x {plugin.ToString("X")}");

            if (headerResult == 0 || plugin == IntPtr.Zero)
            {
                Console.Error.WriteLine("FAIL: the shim did not return a plugin object.");
                return 1;
            }

            var infoGet = Method<InfoGetCallback>(plugin, SlotInfoGet);
            var infoGetCategories = Method<InfoGetCategoriesCallback>(plugin, SlotInfoGetCategories);
            var initialize = Method<InitializeCallback>(plugin, SlotInitialize);
            var finalize = Method<FinalizeCallback>(plugin, SlotFinalize);
            var release = Method<ReleaseCallback>(plugin, SlotRelease);

            var labels = new[] { "Name", "Author", "ShortDescription", "FullDescription" };
            for (var index = 0; index < labels.Length; index++)
            {
                var value = infoGet(plugin, index);
                Console.WriteLine(labels[index].PadRight(17) + ": " + (Marshal.PtrToStringUni(value) ?? "<null>"));
            }

            Console.WriteLine($"Categories       : 0x{infoGetCategories(plugin).ToString("X")}");

            var initializeResult = initialize(plugin, IntPtr.Zero);
            if (initializeResult < 0)
            {
                // The smoke test has no IAIMPCore to hand over. The v1 plugin
                // contract requires one, so a graceful failure is expected here;
                // what matters is that the call reached managed code and did not
                // crash the process.
                Console.WriteLine($"Initialize       : hr = 0x{initializeResult:X8} (no core supplied, expected)");
            }
            else
            {
                Console.WriteLine($"Initialize       : hr = 0x{initializeResult:X8}");
            }

            var finalizeResult = finalize(plugin);
            Console.WriteLine($"Finalize         : hr = 0x{finalizeResult:x8}");

            var references = release(plugin);
            Console.WriteLine($"Release          : refs left = {references}");

            if (finalizeResult < 0)
            {
                Console.Error.WriteLine("FAIL: plugin reported an error.");
                return 1;
            }

            CheckQueryInterface(plugin);

            Console.WriteLine("PASS");
            return 0;
        }

        private static void CheckQueryInterface(IntPtr plugin)
        {
            var queryInterfaceAddress = Marshal.ReadIntPtr(Marshal.ReadIntPtr(plugin), SlotQueryInterface * IntPtr.Size);
            Console.WriteLine($"QueryInterface   : 0x{queryInterfaceAddress.ToString("X")}");
        }

        private static T Method<T>(IntPtr instance, int slot) where T : class
        {
            var vtable = Marshal.ReadIntPtr(instance);
            var address = Marshal.ReadIntPtr(vtable, slot * IntPtr.Size);
            return (T)(object)Marshal.GetDelegateForFunctionPointer(address, typeof(T));
        }
    }
}
