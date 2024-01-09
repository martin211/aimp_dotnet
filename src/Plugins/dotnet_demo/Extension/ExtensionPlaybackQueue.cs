using AIMP.SDK;
using AIMP.SDK.Player.Extensions;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Playlist.Objects;

namespace DemoPlugin.Extension
{
    public class ExtensionPlaybackQueue : IAimpExtensionPlaybackQueue2
    {
        public AimpActionResult GetNext(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult GetPrev(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public void OnSelect(IAimpPlaylistItem item, IAimpPlaybackQueueItem queueItem)
        {
            
        }

        public AimpActionResult<PlaybackQueueInfo> GetInfo(IAimpPlaylistItem item)
        {
            return new AimpActionResult<PlaybackQueueInfo>(ActionResultType.OK);
        }
    }
}