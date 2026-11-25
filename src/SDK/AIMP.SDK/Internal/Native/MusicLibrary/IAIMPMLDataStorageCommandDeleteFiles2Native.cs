using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataStorageCommandDeleteFiles2</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4453-436D-6444656C3200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataStorageCommandDeleteFiles2Native
    {
        [PreserveSig]
        int CanDelete(int physically);

        [PreserveSig]
        int Delete(IntPtr files, int physically);

        [PreserveSig]
        int Delete2(IntPtr filter, int physically);
    }
}