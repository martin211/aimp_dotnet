//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Represents the preset for standard grouping.
    /// Implements the <see cref="AIMP.SDK.MusicLibrary.Presets.IAimpGroupingPreset" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.MusicLibrary.Presets.IAimpGroupingPreset" />
    public interface IAimpGroupingPresetStandard : IAimpGroupingPreset
    {
        /// <summary>
        /// Gets or sets the fields that used for grouping at filter.
        /// </summary>
        /// <value>The fields.</value>
        IAimpObjectList<IAimpSortItem> Fields { get; set; }

        /// <summary>
        /// Gets the used filter.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpDataFilterGroup&gt;.</returns>
        AimpActionResult<IAimpDataFilterGroup> GetFilter();
    }
}
