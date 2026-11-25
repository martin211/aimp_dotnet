using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPExtensionFileInfoProvider</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7446-696C-65496E666F00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionFileInfoProviderNative
    {
        [PreserveSig]
        int GetFileInfo(IntPtr fileUri, IntPtr info);
    }
}