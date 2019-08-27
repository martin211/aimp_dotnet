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
using System;
using System.Collections;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Playlist
{
    [Flags]
    public enum PreimageFlags
    {
        None = 0,
        AIMP_PLAYLIST_ADD_FLAGS_NOCHECKFORMAT = 1,
        AIMP_PLAYLIST_ADD_FLAGS_NOEXPAND = 2,
        AIMP_PLAYLIST_ADD_FLAGS_NOTHREADING = 4,
        AIMP_PLAYLIST_ADD_FLAGS_FILEINFO = 8
    }

    /// <summary>
    /// Provides data for smart-playlist.
    /// </summary>
    public interface IAimpPlaylistPreimageDataProvider
    {
        /// <summary>
        /// Gets the files.
        /// </summary>
        /// <param name="owner">The owner.</param>
        /// <param name="preimageFlags">The preimage flags.</param>
        /// <param name="dataList">The data list.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult GetFiles(IAimpTaskOwner owner, out int preimageFlags, out IList dataList);
    }
}