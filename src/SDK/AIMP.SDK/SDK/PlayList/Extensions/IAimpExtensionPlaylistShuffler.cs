using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList.Extensions;

/// <summary>
/// Custom playlist shuffler (AIMP 6.0+).
/// </summary>
public interface IAimpExtensionPlaylistShuffler : IAimpExtension
{
    AimpActionResult Shuffle(IAimpPlaylist playlist, IAimpObjectList2 list, int initialPlaybackQueueIndex);
}