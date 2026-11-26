using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPExtensionFileExpander</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7446-696C-654578706472")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionFileExpanderNative
    {
        [PreserveSig]
        int Expand(IntPtr fileName, out IntPtr list, IntPtr progressCallback);
    }
}