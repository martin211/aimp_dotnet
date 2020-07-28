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

using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Represents the preset for standard grouping.
    /// </summary>
    public interface IAimpGroupingPresetStandard : IAimpGroupingPreset
    {
        /// <summary>
        /// Gets or sets the fields that used for grouping at filter.
        /// </summary>
        IAimpObjectList<string> Fields { get; set; }

        /// <summary>
        /// Gets the used filter.
        /// </summary>
        AimpActionResult<IAimpDataFilterGroup> GetFilter();
    }
}