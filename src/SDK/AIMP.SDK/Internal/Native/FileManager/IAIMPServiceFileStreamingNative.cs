using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileStreaming</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-696C-655374726D00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileStreamingNative
    {
        [PreserveSig]
        int CreateStreamForFile(IntPtr fileName, uint flags, long offset, long size, out IntPtr stream);

        [PreserveSig]
        int CreateStreamForFileURI(IntPtr fileUri, out IntPtr virtualFile, out IntPtr stream);
    }
}