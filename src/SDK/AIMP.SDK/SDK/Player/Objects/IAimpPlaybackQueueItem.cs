using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.Player.Objects;

/// <summary>
/// Interface IAimpPlaybackQueueItem
/// </summary>
public interface IAimpPlaybackQueueItem
{
    /// <summary>
    /// Gets or sets the user data.
    /// </summary>
    /// <value>The user data.</value>
    object UserData { get; set; }

    /// <summary>
    /// Gets or sets the playlist item.
    /// </summary>
    /// <value>The playlist item.</value>
    IAimpPlaylistItem PlaylistItem { get; set; }

    double Offset { get; set; }
}