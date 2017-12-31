using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace AIMP.DotNet.MusicLibrary.Preimage
{
    public class PlaylistManagerListener : IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }
    }
}