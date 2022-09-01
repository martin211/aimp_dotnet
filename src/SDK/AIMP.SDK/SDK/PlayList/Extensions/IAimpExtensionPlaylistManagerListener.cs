//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.Playlist.Extensions
{
    /// <summary>
    /// Delegate for playlist events.
    /// </summary>
    /// <param name="playlistName">Name of the playlist.</param>
    /// <param name="playlistId">The playlist identifier.</param>
    public delegate void PlayListHandler(string playlistName, string playlistId);

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
}
