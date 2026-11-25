using System;

namespace AIMP.SDK.MusicLibrary.DataStorage;

/// <summary>
/// Enum AimpDataFieldFlagsType
/// </summary>
[Flags]
public enum AimpDataFieldFlagsType
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// The grouping
    /// </summary>
    Grouping = 1,

    /// <summary>
    /// The filtering
    /// </summary>
    Filtering = 2,

    /// <summary>
    /// The internal
    /// </summary>
    Internal = 4,

    /// <summary>
    /// The required
    /// </summary>
    Required = 8
}