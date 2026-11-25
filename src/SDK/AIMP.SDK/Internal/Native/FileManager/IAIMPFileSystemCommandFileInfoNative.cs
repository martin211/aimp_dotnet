using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCommandFileInfo</c> (AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41465343-6D64-4669-6C65-457869737470")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandFileInfoNative
    {
        [PreserveSig]
        int GetFileAttrs(IntPtr fileName, IntPtr attrs);

        [PreserveSig]
        int GetFileSize(IntPtr fileName, out long size);

        [PreserveSig]
        int IsFileExists(IntPtr fileName);
    }
}