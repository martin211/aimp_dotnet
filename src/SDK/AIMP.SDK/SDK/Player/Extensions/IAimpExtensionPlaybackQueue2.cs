using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.Player.Extensions;

public class PlaybackQueueInfo
{
    public int Position { get; }

    public int Size { get; }
}

/// <summary>
/// Extends an abilities of the <see cref="IAimpExtensionPlaybackQueue"/>.
/// </summary>
public interface IAimpExtensionPlaybackQueue2 : IAimpExtensionPlaybackQueue
{
    /// <summary>
    /// Returns information about the queue size and position of the Current item in it.
    /// </summary>
    AimpActionResult<PlaybackQueueInfo> GetInfo(IAimpPlaylistItem item);
}