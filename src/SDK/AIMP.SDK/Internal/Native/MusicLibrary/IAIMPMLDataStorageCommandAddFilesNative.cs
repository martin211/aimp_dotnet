using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataStorageCommandAddFiles</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4453-436D-644164640000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataStorageCommandAddFilesNative
    {
        [PreserveSig]
        int Add(IntPtr files);
    }
}