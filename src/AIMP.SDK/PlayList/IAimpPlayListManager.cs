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
        ActionResultType CreatePlaylist(string name, bool isActive, out IAimpPlaylist playList);

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
        ActionResultType CreatePlaylistFromFile(string fileName, bool isActive, out IAimpPlaylist playList);

        /// <summary>
        /// Gets the current active playlist.
        /// </summary>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        ActionResultType GetActivePlaylist(out IAimpPlaylist playList);

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
        ActionResultType GetPlayablePlaylist(out IAimpPlaylist playList);

        /// <summary>
        /// Gets the loaded playlist.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        ActionResultType GetLoadedPlaylist(int index, out IAimpPlaylist playList);

        /// <summary>
        /// Gets the loaded playlist by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        ActionResultType GetLoadedPlaylistById(string id, out IAimpPlaylist playList);

        /// <summary>
        /// Gets the loaded playlist by name.
        /// </summary>
        /// <param name="name">The name.</param>
        /// <param name="playList">The playlist <see cref="IAimpPlaylist"/>.</param>
        /// <returns>The <see cref="ActionResultType"/>result.</returns>
        ActionResultType GetLoadedPlaylistByName(string name, out IAimpPlaylist playList);

        /// <summary>
        /// Gets the loaded playlist count.
        /// </summary>
        int GetLoadedPlaylistCount();
    }
}