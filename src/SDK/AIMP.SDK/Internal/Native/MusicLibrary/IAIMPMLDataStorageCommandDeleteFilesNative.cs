using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataStorageCommandDeleteFiles</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4453-436D-6444656C0000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataStorageCommandDeleteFilesNative
    {
        [PreserveSig]
        int CanDelete(int physically);

        [PreserveSig]
        int Delete(IntPtr files, int physically);
    }
}