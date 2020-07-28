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

using System.Collections.Generic;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Allow access to preset for data storage.
    /// </summary>
    public interface IAimpGroupingPresets
    {
        /// <summary>
        /// Adds new grouping template with custom data provider <seealso cref="IAimpGroupingTreeDataProvider"/>.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="name">Template name.</param>
        /// <param name="provider">Custom data provider <seealso cref="IAimpGroupingTreeDataProvider"/>.</param>
        AimpActionResult<IAimpGroupingPreset> Add(string id, string name, IAimpGroupingTreeDataProvider provider);

        /// <summary>
        /// Adds new grouping template with default data provider.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="name">Template name.</param>
        /// <param name="fieldNames">The list of fields</param>
        AimpActionResult<IAimpGroupingPresetStandard> Add(string id, string name, IList<string> fieldNames);

        /// <summary>
        /// Adds new grouping template with default data provider.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="name">Template name.</param>
        /// <param name="fieldName">The field name.</param>
        AimpActionResult<IAimpGroupingPresetStandard> Add(string id, string name, string fieldName);

        /// <summary>
        /// Adds blocking on sending notifications during changes.
        /// Use it if you want to change multiple properties at the same time.
        /// </summary>
        void BeginUpdate();

        /// <summary>
        /// Removes blocking on sending notifications.
        /// </summary>
        void EndUpdate();

        /// <summary>
        /// Removes a template by index.
        /// </summary>
        /// <param name="index">Index.</param>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Gets the grouping preset by index.
        /// </summary>
        /// <param name="index">Index.</param>
        AimpActionResult<IAimpGroupingPreset> GetPreset(int index);

        /// <summary>
        /// Gets the standard grouping preset by index.
        /// </summary>
        /// <param name="index">Index.</param>
        AimpActionResult<IAimpGroupingPresetStandard> GetStandardPreset(int index);

        /// <summary>
        /// Gets the grouping preset by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        AimpActionResult<IAimpGroupingPreset> GetPresetById(string id);

        /// <summary>
        /// Gets the standard grouping preset by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        AimpActionResult<IAimpGroupingPresetStandard> GetStandardPresetById(string id);

        /// <summary>
        /// Gets the count of presets.
        /// </summary>
        int GetCount();
    }
}