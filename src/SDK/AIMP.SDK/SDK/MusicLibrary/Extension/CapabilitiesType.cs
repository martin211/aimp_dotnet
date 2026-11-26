using System;
using AIMP.SDK.PlayList.Extensions;

namespace AIMP.SDK.MusicLibrary.Extension;

/// <summary>
/// Enum CapabilitiesType
/// </summary>
[Flags]
public enum CapabilitiesType
{
    /// <summary>
    /// The storage implements data filtering by itself.
    /// Otherwise - data filtering will be processed by Music Library engine.
    /// </summary>
    Filtering = 1,

    /// <summary>
    /// Allows to user to create smart-playlist based on this data storage (this option has no effect to the <see cref="IAimpExtensionPlaylistPreimageFactory"/> implementation).
    /// </summary>
    Preimages = 2,

    /// <summary>
    /// The grouping presets
    /// </summary>
    GroupingPresets = 4,

    /// <summary>
    /// Allows to user customize list of fields that used for grouping and group details.
    /// </summary>
    CustomizeGroups = 8,

    AutoExpandFields = 16,

    /// <summary>
    /// Switching off saving / restoring of grouping tree selection.
    /// May be useful if restoring the selection takes too much time.
    /// </summary>
    NoBookMarks = 32
}