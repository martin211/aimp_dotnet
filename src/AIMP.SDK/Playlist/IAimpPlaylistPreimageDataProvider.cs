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

using System;
using System.Collections;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Playlist
{
    /// <summary>
    ///     Enum PreimageFlags
    /// </summary>
    [Flags]
    public enum PreimageFlags
    {
        /// <summary>
        ///     The none
        /// </summary>
        None = 0,

        /// <summary>
        ///     The aimp playlist add flags nocheckformat
        /// </summary>
        AIMP_PLAYLIST_ADD_FLAGS_NOCHECKFORMAT = 1,

        /// <summary>
        ///     The aimp playlist add flags noexpand
        /// </summary>
        AIMP_PLAYLIST_ADD_FLAGS_NOEXPAND = 2,

        /// <summary>
        ///     The aimp playlist add flags nothreading
        /// </summary>
        AIMP_PLAYLIST_ADD_FLAGS_NOTHREADING = 4,

        /// <summary>
        ///     The aimp playlist add flags fileinfo
        /// </summary>
        AIMP_PLAYLIST_ADD_FLAGS_FILEINFO = 8
    }

    /// <summary>
    ///     Provides data for smart-playlist.
    /// </summary>
    public interface IAimpPlaylistPreimageDataProvider
    {
        /// <summary>
        ///     Gets the files.
        /// </summary>
        /// <param name="owner">The owner.</param>
        /// <returns>Item1 - pre image flag, item2 - the data list.</returns>
        AimpActionResult<int, IList> GetFiles(IAimpTaskOwner owner);
    }
}