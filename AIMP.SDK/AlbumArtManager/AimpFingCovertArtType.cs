namespace AIMP.SDK.AlbumArtManager
{
    using System;

    /// <summary>
    /// 
    /// </summary>
    [Flags]
    public enum AimpFingCovertArtType
    {
        None,
        AIMP_SERVICE_ALBUMART_FLAGS_IGNORECACHE = 1,
        AIMP_SERVICE_ALBUMART_FLAGS_ORIGINAL = 2,
        AIMP_SERVICE_ALBUMART_FLAGS_WAITFOR = 4
    }
}