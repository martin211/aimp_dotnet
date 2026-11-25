using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCommandStreaming</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41465343-6D64-5374-7265-616D696E6700")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandStreamingNative
    {
        [PreserveSig]
        int CreateStream(IntPtr fileName, long offset, long size, uint flags, out IntPtr stream);
    }
}