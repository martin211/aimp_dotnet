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

using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataStorage
    {
        /// <summary>
        /// Gets the storage identifier.
        /// </summary>
        string Id { get; }

        /// <summary>
        /// Gets the storage caption.
        /// </summary>
        string Caption { get; }

        /// <summary>
        /// Gets or sets the current grouping preset.
        /// </summary>
        IAimpGroupingPreset GroupingPreset { get; set; }
    }
}