using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileSystems</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-5300-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileSystemsNative
    {
        [PreserveSig]
        int Get(IntPtr fileUri, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetDefault(ref Guid iid, out IntPtr obj);
    }
}