using System;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum PlaylistDeleteFlags
/// </summary>
[Flags]
public enum PlaylistDeleteFlags
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// The physically
    /// </summary>
    Physically = 1,

    /// <summary>
    /// The no confirmation
    /// </summary>
    NoConfirmation = 2
}