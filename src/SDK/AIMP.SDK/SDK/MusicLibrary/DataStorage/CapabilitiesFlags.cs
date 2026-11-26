using System;

namespace AIMP.SDK.MusicLibrary.DataStorage;

/// <summary>
/// Enum CapabilitiesFlags
/// </summary>
[Flags]
public enum CapabilitiesFlags
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// The hide all data
    /// </summary>
    HideAllData = 1,

    /// <summary>
    /// The dont sort
    /// </summary>
    DontSort = 2
}