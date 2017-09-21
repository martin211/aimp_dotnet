using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Provides an access to preimage settings that based on one of data storages of Music Library.
    /// Note that some data storage has no support of preimages.
    /// </summary>
    /// <seealso cref="Playlist.IAimpPlaylistPreimage" />
    public interface IAimpPlaylistPreimage : Playlist.IAimpPlaylistPreimage
    {
        /// <summary>
        /// Gets the filter.
        /// </summary>
        /// <param name="filter">All changes in the Filter will be automatically applied to the preimage.
        /// Use the BeginUpdate / EndUpdate methods to change few settings at one time.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFilter(out IAimpDataFieldFilter filter);

        /// <summary>
        /// Gets the storage.
        /// </summary>
        /// <param name="storage">The storage.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult" /></returns>
        AimpActionResult GetStorage(out IAimpDataStorage storage);
    }
}