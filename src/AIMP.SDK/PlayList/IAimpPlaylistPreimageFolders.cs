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
    ///     Interface IAimpPlaylistPreimageFolders
    ///     Implements the <see cref="AIMP.SDK.Playlist.IAimpPlaylistPreimage" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.Playlist.IAimpPlaylistPreimage" />
    public interface IAimpPlaylistPreimageFolders : IAimpPlaylistPreimage
    {
        /// <summary>
        ///     Itemses the add.
        /// </summary>
        /// <param name="path">The path.</param>
        /// <param name="recursive">if set to <c>true</c> [recursive].</param>
        AimpActionResult ItemsAdd(string path, bool recursive);

        /// <summary>
        ///     Itemses the delete.
        /// </summary>
        /// <param name="index">The index.</param>
        AimpActionResult ItemsDelete(int index);

        /// <summary>
        ///     Itemses the delete all.
        /// </summary>
        AimpActionResult ItemsDeleteAll();

        /// <summary>
        ///     Get the items by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="path">The path.</param>
        /// <param name="recursive">if set to <c>true</c> [recursive].</param>
        /// <returns>Item1 - path, Item2 - recursive or not.</returns>
        AimpActionResult<string, bool> ItemsGet(int index);

        /// <summary>
        ///     Itemses the get count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int ItemsGetCount();
    }
}