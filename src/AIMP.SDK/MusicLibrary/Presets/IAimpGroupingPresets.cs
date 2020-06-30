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
        /// <param name="preset">Created preset <seealso cref="IAimpGroupingPreset"/>.</param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Add(string id, string name, IAimpGroupingTreeDataProvider provider,
            out IAimpGroupingPreset preset);

        /// <summary>
        /// Adds new grouping template with default data provider.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="name">Template name.</param>
        /// <param name="fieldNames">The list of fields</param>
        /// <param name="preset">Created preset <seealso cref="IAimpGroupingPresetStandard"/>.</param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Add(string id, string name, IList<string> fieldNames, out IAimpGroupingPresetStandard preset);

        /// <summary>
        /// Adds new grouping template with default data provider.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="name">Template name.</param>
        /// <param name="fieldName">The field name.</param>
        /// <param name="preset">Created preset <seealso cref="IAimpGroupingPresetStandard"/>.</param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Add(string id, string name, string fieldName, out IAimpGroupingPresetStandard preset);

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
        /// Removes a template by idex.
        /// </summary>
        /// <param name="index">Index.</param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Delete(int index);

        /// <summary>
        /// Gets the grouping preset by index.
        /// </summary>
        /// <param name="index">Index.</param>
        /// <param name="preset">The grouping preset <seealso cref="IAimpGroupingPreset"/>.</param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Get(int index, out IAimpGroupingPreset preset);

        /// <summary>
        /// Gets the standard grouping preset by index.
        /// </summary>
        /// <param name="index">Index.</param>
        /// <param name="preset">The snadart grouping preset <seealso cref="IAimpGroupingPresetStandard"/></param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType Get(int index, out IAimpGroupingPresetStandard preset);

        /// <summary>
        /// Gets the grouping preset by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="preset">The grouping preset <seealso cref="IAimpGroupingPreset"/>.</param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetById(string id, out IAimpGroupingPreset preset);

        /// <summary>
        /// Gets the standard grouping preset by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="preset">The snadart grouping preset <seealso cref="IAimpGroupingPresetStandard"/></param>
        /// <returns>The operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetById(string id, out IAimpGroupingPresetStandard preset);

        /// <summary>
        /// Gets the count of presets.
        /// </summary>
        int GetCount();
    }
}