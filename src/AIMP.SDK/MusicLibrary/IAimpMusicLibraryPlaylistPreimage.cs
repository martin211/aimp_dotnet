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
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Provides an access to preimage settings that based on one of data storages of Music Library.
    /// Note that some data storage has no support of preimages.
    /// </summary>
    /// <seealso cref="Playlist.IAimpPlaylistPreimage" />
    public interface IAimpMusicLibraryPlaylistPreimage : Playlist.IAimpPlaylistPreimage
    {
        /// <summary>
        /// Gets the filter.
        /// </summary>
        /// <param name="filter">All changes in the Filter will be automatically applied to the preimage.
        /// Use the BeginUpdate / EndUpdate methods to change few settings at one time.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetFilter(out IAimpDataFieldFilter filter);

        /// <summary>
        /// Gets the storage.
        /// </summary>
        /// <param name="storage">The storage.</param>
        /// <returns>Operation result <seealso cref="ActionResultType" /></returns>
        ActionResultType GetStorage(out IAimpDataStorage storage);
    }
}