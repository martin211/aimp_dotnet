using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Player;
using AIMP.SDK;
using AIMP.SDK.PlayList.Extensions;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpExtensionPlaylistManagerListener"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class PlaylistListenerBridge : IAIMPExtensionPlaylistManagerListenerNative
    {
        private readonly IAimpExtensionPlaylistManagerListener _listener;

        public PlaylistListenerBridge(IAimpExtensionPlaylistManagerListener listener)
        {
            _listener = listener ?? throw new ArgumentNullException(nameof(listener));
        }

        [PreserveSig]
        public void PlaylistActivated(IntPtr playlist)
        {
            Invoke(playlist, _listener.OnPlaylistActivated);
        }

        [PreserveSig]
        public void PlaylistAdded(IntPtr playlist)
        {
            Invoke(playlist, _listener.OnPlaylistAdded);
        }

        [PreserveSig]
        public void PlaylistRemoved(IntPtr playlist)
        {
            Invoke(playlist, _listener.OnPlaylistRemoved);
        }

        private static void Invoke(IntPtr pointer, Func<IAimpPlaylist, AimpActionResult> callback)
        {
            Safe.Run(() =>
            {
                if (pointer == IntPtr.Zero || callback == null)
                {
                    return;
                }

                using (var playlist = AimpPlaylistWrapper.FromBorrowed(pointer))
                {
                    callback(playlist);
                }
            });
        }
    }
}