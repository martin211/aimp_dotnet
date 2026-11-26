using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCommandDropSource</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41465343-6D64-4472-6F70-537263000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandDropSourceNative
    {
        [PreserveSig]
        int CreateStream(IntPtr fileName, out IntPtr stream);
    }
}