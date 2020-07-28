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

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    ///     Allow access to grouping preset.
    /// </summary>
    public interface IAimpGroupingPreset
    {
        /// <summary>
        ///     Gets or sets the user custom data.
        /// </summary>
        /// <value>The custom.</value>
        string Custom { get; set; }

        /// <summary>
        ///     Gets or sets the preset identifier.
        /// </summary>
        /// <value>The identifier.</value>
        string Id { get; set; }

        /// <summary>
        ///     Gets or sets the preset name.
        /// </summary>
        /// <value>The name.</value>
        string Name { get; set; }
    }
}