using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileInfo</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-696C-65496E666F00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileInfoNative
    {
        [PreserveSig]
        int GetFileInfoFromFileURI(IntPtr fileUri, uint flags, IntPtr info);

        [PreserveSig]
        int GetFileInfoFromStream(IntPtr stream, uint flags, IntPtr info);

        [PreserveSig]
        int GetVirtualFile(IntPtr fileUri, uint flags, out IntPtr info);
    }
}