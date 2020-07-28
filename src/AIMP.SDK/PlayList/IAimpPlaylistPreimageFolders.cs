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
        /// <returns>ActionResultType.</returns>
        ActionResultType ItemsAdd(string path, bool recursive);

        /// <summary>
        ///     Itemses the delete.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType ItemsDelete(int index);

        /// <summary>
        ///     Itemses the delete all.
        /// </summary>
        /// <returns>ActionResultType.</returns>
        ActionResultType ItemsDeleteAll();

        /// <summary>
        ///     Itemses the get.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="path">The path.</param>
        /// <param name="recursive">if set to <c>true</c> [recursive].</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType ItemsGet(int index, out string path, out bool recursive);

        /// <summary>
        ///     Itemses the get count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int ItemsGetCount();
    }
}