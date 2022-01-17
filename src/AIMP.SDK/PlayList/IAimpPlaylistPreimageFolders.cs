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
    /// Interface IAimpPlaylistPreimageFolders
    /// Implements the <see cref="AIMP.SDK.Playlist.IAimpPlaylistPreimage" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.Playlist.IAimpPlaylistPreimage" />
    public interface IAimpPlaylistPreimageFolders : IAimpPlaylistPreimage
    {
        /// <summary>
        /// Adds a new items.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <param name="recursive">if set to <c>true</c> [recursive].</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult ItemsAdd(string path, bool recursive);

        /// <summary>
        /// Delete item by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult ItemsDelete(int index);

        /// <summary>
        /// Delete all items.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult ItemsDeleteAll();

        /// <summary>
        /// Get the items by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>Item1 - path, Item2 - recursive or not.</returns>
        AimpActionResult<string, bool> ItemsGet(int index);

        /// <summary>
        /// Get count of items at playlist.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int ItemsGetCount();
    }
}
