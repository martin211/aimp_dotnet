using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCustomFileCommand</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41465343-6D64-4465-6C65-746500000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandDeleteNative
    {
        [PreserveSig]
        int CanProcess(IntPtr fileName);

        [PreserveSig]
        int Process(IntPtr fileName);
    }
}