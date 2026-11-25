using System;

namespace AIMP.SDK.PlayList.Objects;

/// <summary>
/// Enum ReloadInfoFlags
/// </summary>
[Flags]
public enum ReloadInfoFlags
{
    /// <summary>
    /// Information will be updated for files that does not have it.
    /// </summary>
    AIMP_PLAYLIST_RELOADINFO_FLAGS_DEFAULT,

    /// <summary>
    /// Information will be updated for all files.
    /// </summary>
    AIMP_PLAYLIST_RELOADINFO_FLAGS_FULL,

    /// <summary>
    /// Information will be updated for selected files.
    /// </summary>
    AIMP_PLAYLIST_RELOADINFO_FLAGS_SELECTED
}