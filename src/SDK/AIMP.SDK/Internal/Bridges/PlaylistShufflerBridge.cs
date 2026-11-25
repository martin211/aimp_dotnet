using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Player;
using AIMP.SDK.PlayList.Extensions;

namespace AIMP.Internal.Bridges;

/// <summary>
/// CCW adapter for <see cref="IAimpExtensionPlaylistShuffler"/>.
/// </summary>
[ComVisible(true)]
[ClassInterface(ClassInterfaceType.None)]
internal sealed class PlaylistShufflerBridge : IAIMPExtensionPlaylistShufflerNative
{
    private readonly IAimpExtensionPlaylistShuffler _shuffler;

    public PlaylistShufflerBridge(IAimpExtensionPlaylistShuffler shuffler)
    {
        _shuffler = shuffler ?? throw new ArgumentNullException(nameof(shuffler));
    }

    public int Shuffle(IntPtr playlist, IntPtr list, int initialPlaybackQueueIndex)
    {
        return Safe.Run(() =>
        {
            var playlistWrapper = AimpPlaylistWrapper.FromBorrowed(playlist);
            var listWrapper = list == IntPtr.Zero
                ? null
                : new AimpObjectListWrapper(new AimpObjectList(AimpComHelper.AddRef(list)));

            try
            {
                return (int)_shuffler.Shuffle(playlistWrapper, listWrapper, initialPlaybackQueueIndex).ResultType;
            }
            finally
            {
                playlistWrapper?.Dispose();
                listWrapper?.Dispose();
            }
        });
    }
}