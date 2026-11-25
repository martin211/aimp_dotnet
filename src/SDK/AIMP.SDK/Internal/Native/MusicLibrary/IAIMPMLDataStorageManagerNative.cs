using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataStorageManager</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4453-4D6E-677200000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataStorageManagerNative
    {
        [PreserveSig]
        void BackgroundTaskStarted(int id, IntPtr caption, IntPtr cancelEvent);

        [PreserveSig]
        void BackgroundTaskFinished(int id);

        [PreserveSig]
        void Changed();
    }
}