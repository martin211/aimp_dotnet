using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.Player.Extensions;

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