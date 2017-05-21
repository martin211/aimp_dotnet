using AIMP.SDK.Playlist;

namespace AIMP.SDK.Playback
{
    public interface IAimpPlaybackQueueItem
    {
        object UserData { get; set; }

        IAimpPlaylistItem PlaylistItem { get; set; }
    }
}