using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPFileSystemCommandOpenFileFolder</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41465343-6D64-4669-6C65-466C64720000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileSystemCommandOpenFileFolderNative
    {
        [PreserveSig]
        int CanProcess(IntPtr fileName);

        [PreserveSig]
        int Process(IntPtr fileName);
    }
}