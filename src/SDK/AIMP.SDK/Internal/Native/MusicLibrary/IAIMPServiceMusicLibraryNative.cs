using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPServiceMusicLibrary</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764D-4C00-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceMusicLibraryNative
    {
        [PreserveSig]
        int GetActiveStorage(ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int SetActiveStorage(IntPtr storage);

        [PreserveSig]
        int GetStorage(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetStorageByID(IntPtr id, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetStorageCount();
    }
}