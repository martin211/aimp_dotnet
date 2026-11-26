using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPExtensionFileInfoProviderEx</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7446-696C-65496E666F45")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPExtensionFileInfoProviderExNative
    {
        [PreserveSig]
        int GetFileInfo(IntPtr stream, IntPtr info);
    }
}