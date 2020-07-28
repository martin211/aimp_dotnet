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

using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary
{
    /// <summary>
    /// Provides an access to data storages of Music Library.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceMusicLibrary : IAimpService
    {
        /// <summary>
        /// Gets the active data storage.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpDataStorage&gt;.</returns>
        AimpActionResult<IAimpDataStorage> GetActiveStorage();

        /// <summary>
        /// Gets the active grouping preset.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpGroupingPresets&gt;.</returns>
        AimpActionResult<IAimpGroupingPresets> GetActiveGroupingPresets();

        /// <summary>
        /// Sets the active data storage.
        /// </summary>
        /// <param name="storage">The data storage.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetActiveStorage(IAimpDataStorage storage);

        /// <summary>
        /// Sets the active storage.
        /// </summary>
        /// <param name="preset">The grouping preset.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetActiveStorage(IAimpGroupingPresets preset);

        /// <summary>
        /// Gets the data storage by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpDataStorage&gt;.</returns>
        AimpActionResult<IAimpDataStorage> GetStorage(int index);

        /// <summary>
        /// Gets the grouping preset by index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpGroupingPresets&gt;.</returns>
        AimpActionResult<IAimpGroupingPresets> GetGroupingPresets(int index);

        /// <summary>
        /// Gets the data storage by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>AimpActionResult&lt;IAimpDataStorage&gt;.</returns>
        AimpActionResult<IAimpDataStorage> GetStorageById(string id);

        /// <summary>
        /// Gets the grouping preset by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>AimpActionResult&lt;IAimpGroupingPresets&gt;.</returns>
        AimpActionResult<IAimpGroupingPresets> GetGroupingPresetsById(string id);

        /// <summary>
        /// Gets the storage count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetStorageCount();
    }
}