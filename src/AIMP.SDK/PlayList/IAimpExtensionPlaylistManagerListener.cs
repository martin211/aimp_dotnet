// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// Delegate for playlist events.
    /// </summary>
    /// <param name="playlistName">Name of the playlist.</param>
    /// <param name="playlistId">The playlist identifier.</param>
    public delegate void PlayListHandler(string playlistName, string playlistId);

    /// <summary>
    /// This is extension for <see cref="IAimpPlaylistManager"/> service, provides an ability to receive notifications about the changes in manager.
    /// </summary>
    public interface IAimpExtensionPlaylistManagerListener
    {
        /// <summary>
        /// Occurs when playlist activated.
        /// </summary>
        ActionResultType OnPlaylistActivated(IAimpPlaylist playlist);

        /// <summary>
        /// Occurs when playlist added.
        /// </summary>
        ActionResultType OnPlaylistAdded(IAimpPlaylist playlist);

        /// <summary>
        /// Occurs when playlist removed.
        /// </summary>
        ActionResultType OnPlaylistRemoved(IAimpPlaylist playlist);
    }
}