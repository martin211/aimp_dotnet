using AIMP.SDK.PlayList.Objects;

namespace AIMP.SDK.PlayList.Extensions;

/// <summary>
/// This is extension for <see cref="IAimpServicePlaylistManager" /> service, provides an ability to receive notifications
/// about the changes in manager.
/// </summary>
public interface IAimpExtensionPlaylistManagerListener
{
    /// <summary>
    /// Occurs when playlist activated.
    /// </summary>
    /// <param name="playlist">The playlist.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist);

    /// <summary>
    /// Occurs when playlist added.
    /// </summary>
    /// <param name="playlist">The playlist.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist);

    /// <summary>
    /// Occurs when playlist removed.
    /// </summary>
    /// <param name="playlist">The playlist.</param>
    /// <returns>ActionResultType.</returns>
    AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist);
}