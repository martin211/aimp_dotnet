// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
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
        event PlayListHandler PlaylistActivated;

        /// <summary>
        /// Occurs when playlist added.
        /// </summary>
        event PlayListHandler PlaylistAdded;

        /// <summary>
        /// Occurs when playlist removed.
        /// </summary>
        event PlayListHandler PlaylistRemoved;
    }
}