using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPServicePlaylistManager</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7650-6C73-4D616E000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServicePlaylistManagerNative
    {
        [PreserveSig]
        int CreatePlaylist(IntPtr name, int activate, out IntPtr playlist);

        [PreserveSig]
        int CreatePlaylistFromFile(IntPtr fileName, int activate, out IntPtr playlist);

        [PreserveSig]
        int GetActivePlaylist(out IntPtr playlist);

        [PreserveSig]
        int SetActivePlaylist(IntPtr playlist);

        [PreserveSig]
        int GetPlayingPlaylist(out IntPtr playlist);

        [PreserveSig]
        int GetLoadedPlaylist(int index, out IntPtr playlist);

        [PreserveSig]
        int GetLoadedPlaylistByName(IntPtr name, out IntPtr playlist);

        [PreserveSig]
        int GetLoadedPlaylistCount();

        [PreserveSig]
        int GetLoadedPlaylistByID(IntPtr id, out IntPtr playlist);
    }
}