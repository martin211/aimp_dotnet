using System;

namespace AIMP.SDK.MusicLibrary.DataStorage;

/// <summary>
/// Enum GroupingTreeNodeFlags
/// </summary>
[Flags]
public enum GroupingTreeNodeFlags
{
    /// <summary>
    /// The has children
    /// </summary>
    HasChildren = 1,

    /// <summary>
    /// The standalone
    /// </summary>
    Standalone = 2
}