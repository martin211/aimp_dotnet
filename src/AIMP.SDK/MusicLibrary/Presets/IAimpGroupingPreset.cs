// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Allow access to grouping preset.
    /// </summary>
    public interface IAimpGroupingPreset
    {
        /// <summary>
        /// Gets or sets the user custom data.
        /// </summary>
        string Custom { get; set; }

        /// <summary>
        /// Gets or sets the preset identifier.
        /// </summary>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the preset name.
        /// </summary>
        string Name { get; set; }
    }
}