﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.Playlist;
using AIMP.SDK.Playlist.Objects;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Provides an access to preimage settings that based on one of data storages of Music Library.
    /// Note that some data storage has no support of preimages.
    /// Implements the <see cref="IAimpPlaylistPreimage" />
    /// </summary>
    /// <seealso cref="IAimpPlaylistPreimage" />
    /// <seealso cref="IAimpPlaylistPreimage" />
    public interface IAimpMusicLibraryPlaylistPreimage : IAimpPlaylistPreimage
    {
        /// <summary>
        /// Gets the filter.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpDataFilter&gt;.</returns>
        /// <note>
        /// All changes in the Filter will be automatically applied to the preimage.
        /// Use the BeginUpdate / EndUpdate methods to change few settings at one time.
        /// </note>
        AimpActionResult<IAimpDataFilter> GetFilter();

        /// <summary>
        /// Gets the storage.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpDataStorage&gt;.</returns>
        AimpActionResult<IAimpDataStorage> GetStorage();
    }
}
