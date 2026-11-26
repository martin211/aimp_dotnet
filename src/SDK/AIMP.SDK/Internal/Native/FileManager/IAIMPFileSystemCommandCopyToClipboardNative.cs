using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCommandCopyToClipboard</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41465343-6D64-436F-7079-32436C706264")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandCopyToClipboardNative
    {
        [PreserveSig]
        int CopyToClipboard(IntPtr files);
    }
}