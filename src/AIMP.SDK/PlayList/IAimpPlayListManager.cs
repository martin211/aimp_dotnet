// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Playlist
{
    /// <summary>
    /// The service provides an access to playlist manager.
    /// Implements the <see cref="IAimpServicePlaylistManager2" />
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="IAimpServicePlaylistManager2" />
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServicePlaylistManager : IAimpServicePlaylistManager2, IAimpService
    {
        /// <summary>
        /// Gets the playlist queue.
        /// </summary>
        /// <value>The playlist queue.</value>
        IAimpPlaylistQueue PlaylistQueue { get; }

        /// <summary>
        /// Creates the playlist.
        /// </summary>
        /// <param name="name">The playlist name.
        /// <para>
        /// Automatic name will be applied if name is equals empty value.
        /// </para></param>
        /// <param name="isActive">If set to <c>true</c> playlist will be active.</param>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> CreatePlaylist(string name, bool isActive);

        /// <summary>
        /// Creates the playlist from file.
        /// </summary>
        /// <param name="fileName">Name of the file.
        /// <para>
        /// Automatic name will be applied if name is equals empty value.
        /// </para></param>
        /// <param name="isActive">If set to <c>true</c> playlist will be active.</param>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> CreatePlaylistFromFile(string fileName, bool isActive);

        /// <summary>
        /// Gets the current active playlist.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> GetActivePlaylist();

        /// <summary>
        /// Sets the playlist as active.
        /// </summary>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist" />.</param>
        /// <returns>ActionResultType.</returns>
        AimpActionResult SetActivePlaylist(IAimpPlaylist playList);

        /// <summary>
        /// Gets the playable playlist.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> GetPlayingPlaylist();

        /// <summary>
        /// Gets the loaded playlist by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> GetLoadedPlaylist(int index);

        /// <summary>
        /// Gets the loaded playlist by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> GetLoadedPlaylistById(string id);

        /// <summary>
        /// Gets the loaded playlist by name.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <returns>AimpActionResult&lt;IAimpPlaylist&gt;.</returns>
        AimpActionResult<IAimpPlaylist> GetLoadedPlaylistByName(string name);

        /// <summary>
        /// Gets the loaded playlist count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetLoadedPlaylistCount();
    }
}
