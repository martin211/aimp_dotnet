using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPServicePlaylistManager2</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-536D-504C-4D6E-677232000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServicePlaylistManager2Native
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

        [PreserveSig]
        int GetPreimageFactory(int index, out IntPtr factory);

        [PreserveSig]
        int GetPreimageFactoryByID(IntPtr id, out IntPtr factory);

        [PreserveSig]
        int GetPreimageFactoryCount();
    }
}