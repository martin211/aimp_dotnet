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
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Provides an access to data storages of Music Library.
    /// </summary>
    public interface IAimpServiceMusicLibrary
    {
        /// <summary>
        /// Gets the active data storage.
        /// </summary>
        /// <param name="storage">The data storage.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetActiveStorage(out IAimpDataStorage storage);

        /// <summary>
        /// Gets the active grouping preset.
        /// </summary>
        /// <param name="preset">The grouping preset.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetActiveStorage(out IAimpGroupingPresets preset);

        /// <summary>
        /// Sets the active data storage.
        /// </summary>
        /// <param name="storage">The data storage.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult SetActiveStorage(IAimpDataStorage storage);

        /// <summary>
        /// Sets the active storage.
        /// </summary>
        /// <param name="preset">The grouping preset.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult SetActiveStorage(IAimpGroupingPresets preset);

        /// <summary>
        /// Gets the data storage by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="storage">The data storage.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetStorage(int index, out IAimpDataStorage storage);

        /// <summary>
        /// Gets the grouping preset by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="preset">The grouping preset.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetStorage(int index, out IAimpGroupingPresets preset);

        /// <summary>
        /// Gets the data storage by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="storage">The data storage.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetStorageById(string id, out IAimpDataStorage storage);

        /// <summary>
        /// Gets the grouping preset by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="preset">The grouping preset.</param>
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetStorageById(string id, out IAimpGroupingPresets preset);

        /// <summary>
        /// Gets the storage count.
        /// </summary>
        int GetStorageCount();
    }
}