using System;

namespace AIMP.SDK.AlbumArt;

/// <summary>
/// Enum AimpFindCovertArtType
/// </summary>
[Flags]
public enum AimpFindCovertArtType
{
    /// <summary>
    /// The none
    /// </summary>
    None = 0,

    /// <summary>
    /// The aimp service albumart flags ignorecache
    /// </summary>
    AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE = 1,

    /// <summary>
    /// The aimp service albumart flags original
    /// </summary>
    AIMP_SERVICE_ALBUMART_FLAGS_ORIGINAL = 2,

    /// <summary>
    /// The aimp service albumart flags waitfor
    /// </summary>
    AIMP_SERVICE_ALBUMART_FLAGS_WAITFOR = 4
}