using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPExtensionPlaylistShuffler</c> (apiPlaylists.h, AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7450-6C73-536875666C72")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionPlaylistShufflerNative
    {
        [PreserveSig]
        int Shuffle(IntPtr playlist, IntPtr list, int initialPlaybackQueueIndex);
    }
}