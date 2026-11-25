using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCommandFileInfo</c> before AIMP 6.0.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7446-696C-65496E666F00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandFileInfoLegacyNative
    {
        [PreserveSig]
        int GetFileAttrs(IntPtr fileName, IntPtr attrs);

        [PreserveSig]
        int GetFileSize(IntPtr fileName, out long size);

        [PreserveSig]
        int IsFileExists(IntPtr fileName);
    }
}