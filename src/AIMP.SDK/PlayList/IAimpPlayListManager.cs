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
    /// The service provides an access to playlist manager.
    /// </summary>
    public interface IAimpPlaylistManager
    {
        IAimpPlaylistQueue PlaylistQueue { get; }

        /// <summary>
        /// Creates the playlist.
        /// </summary>
        /// <param name="name">
        /// The playlist name.
        /// <para>
        /// Automatic name will be applied if name is equals empty value.
        /// </para>
        /// </param>
        /// <param name="isActive">If set to <c>true</c> playlist will be active.</param>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult<IAimpPlaylist> CreatePlaylist(string name, bool isActive);

        /// <summary>
        /// Creates the playlist from file.
        /// </summary>
        /// <param name="fileName">
        /// Name of the file.
        /// <para>
        /// Automatic name will be applied if name is equals empty value.
        /// </para>
        /// </param>
        /// <param name="isActive">If set to <c>true</c> playlist will be active.</param>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult<IAimpPlaylist> CreatePlaylistFromFile(string fileName, bool isActive);

        /// <summary>
        /// Gets the current active playlist.
        /// </summary>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult<IAimpPlaylist> GetActivePlaylist();

        /// <summary>
        /// Sets the playlist as active.
        /// </summary>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        ActionResultType SetActivePlaylist(IAimpPlaylist playList);

        /// <summary>
        /// Gets the playable playlist.
        /// </summary>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        AimpActionResult<IAimpPlaylist> GetPlayablePlaylist();

        /// <summary>
        /// Gets the loaded playlist by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>The <see cref="IAimpPlaylist"/>result.</returns>
        AimpActionResult<IAimpPlaylist> GetLoadedPlaylist(int index);

        /// <summary>
        /// Gets the loaded playlist by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="IAimpPlaylist"/>result.</returns>
        AimpActionResult<IAimpPlaylist> GetLoadedPlaylistById(string id);

        /// <summary>
        /// Gets the loaded playlist by name.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <returns>The <see cref="AimpActionResult"/>result.</returns>
        AimpActionResult<IAimpPlaylist> GetLoadedPlaylistByName(string name);

        /// <summary>
        /// Gets the loaded playlist count.
        /// </summary>
        int GetLoadedPlaylistCount();
    }
}