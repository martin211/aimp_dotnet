namespace AIMP.SDK.Visuals
{
    using System;

    [Flags]
    public enum AimpVisualFlags
    {
        AIMP_VISUAL_FLAGS_RQD_DATA_WAVE = 1,
        AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM = 2,
        AIMP_VISUAL_FLAGS_NOT_SUSPEND = 4
    }
}