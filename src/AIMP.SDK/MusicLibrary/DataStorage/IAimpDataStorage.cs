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

using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Interface provides an access to common to all data storages settings.
    /// The <see cref="IAimpGroupingPresets" /> is implemented on same level.
    /// </summary>
    public interface IAimpDataStorage
    {
        /// <summary>
        /// Gets the storage identifier.
        /// </summary>
        /// <value>The identifier.</value>
        string Id { get; }

        /// <summary>
        /// Gets the storage caption.
        /// </summary>
        /// <value>The caption.</value>
        string Caption { get; }

        /// <summary>
        /// Gets or sets the active grouping preset.
        /// </summary>
        /// <value>The grouping preset.</value>
        IAimpGroupingPreset GroupingPreset { get; set; }
    }
}
