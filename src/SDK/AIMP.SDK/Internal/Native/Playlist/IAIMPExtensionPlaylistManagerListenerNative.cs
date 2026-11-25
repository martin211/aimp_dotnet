using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPExtensionPlaylistManagerListener</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7450-6C73-4D616E4C7472")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionPlaylistManagerListenerNative
    {
        [PreserveSig]
        void PlaylistActivated(IntPtr playlist);

        [PreserveSig]
        void PlaylistAdded(IntPtr playlist);

        [PreserveSig]
        void PlaylistRemoved(IntPtr playlist);
    }
}