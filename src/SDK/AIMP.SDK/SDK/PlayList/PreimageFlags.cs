using System;

namespace AIMP.SDK.PlayList;

/// <summary>
/// Enum PreimageFlags
/// </summary>
[Flags]
public enum PreimageFlags
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// The aimp playlist add flags nocheckformat
    /// </summary>
    AIMP_PLAYLIST_ADD_FLAGS_NOCHECKFORMAT = 1,

    /// <summary>
    /// The aimp playlist add flags noexpand
    /// </summary>
    AIMP_PLAYLIST_ADD_FLAGS_NOEXPAND = 2,

    /// <summary>
    /// The aimp playlist add flags nothreading
    /// </summary>
    AIMP_PLAYLIST_ADD_FLAGS_NOTHREADING = 4,

    /// <summary>
    /// The aimp playlist add flags fileinfo
    /// </summary>
    AIMP_PLAYLIST_ADD_FLAGS_FILEINFO = 8
}