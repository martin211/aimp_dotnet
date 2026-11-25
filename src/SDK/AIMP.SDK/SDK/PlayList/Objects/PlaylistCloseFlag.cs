using System;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum PlaylistCloseFlag
/// </summary>
[Flags]
public enum PlaylistCloseFlag
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// Ignores current settings and remove playlist from disk after closing.
    /// </summary>
    ForceRemove = 1,

    /// <summary>
    /// Ignores current settings and not remove playlist from disk after closing.
    /// </summary>
    ForceUnload = 2
}