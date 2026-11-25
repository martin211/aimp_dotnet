using AIMP.SDK;
using AIMP.SDK.PlayList.Extensions;
using AIMP.SDK.PlayList.Objects;

namespace Aimp.MusicLibraryPlugin.Preimage
{
    public class PlaylistManagerListener : IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }
    }
}
