using AIMP.SDK;
using AIMP.SDK.Player.Extensions;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Playlist.Objects;

namespace DemoPlugin.Extension
{
    public class ExtensionPlaybackQueue : IAimpExtensionPlaybackQueue
    {
        private readonly IAimpPlayer _player;

        public ExtensionPlaybackQueue(IAimpPlayer player)
        {
            _player = player;
        }

        public AimpActionResult GetNext(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
        {
            if (queueItem.PlaylistItem != null)
            {
                System.Diagnostics.Debugger.Break();
            }

            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult GetPrev(object current, PlaybackQueueFlags flags, IAimpPlaybackQueueItem queueItem)
        {
            if (queueItem.PlaylistItem != null)
            {
                System.Diagnostics.Debugger.Break();
            }

            return new AimpActionResult(ActionResultType.OK);
        }

        public void OnSelect(IAimpPlaylistItem item, IAimpPlaybackQueueItem queueItem)
        {
            if (queueItem.PlaylistItem != null)
            {
                System.Diagnostics.Debugger.Break();
            }
        }

        public AimpActionResult<PlaybackQueueInfo> GetInfo(IAimpPlaylistItem item)
        {
            return new AimpActionResult<PlaybackQueueInfo>(ActionResultType.OK);
        }
    }
}