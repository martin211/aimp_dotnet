using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistPreimageDataProvider</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-536D-506C-7344-617461507276")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPPlaylistPreimageDataProviderNative
    {
        [PreserveSig]
        int GetFiles(IntPtr owner, out IntPtr flags, out IntPtr list);
    }
}