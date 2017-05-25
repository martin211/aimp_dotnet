// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Visuals
{
    using System;

    [Flags]
    public enum AimpVisualFlags
    {
        /// <summary>
        /// Plugin required WaveForm data for rendering.
        /// </summary>
        AIMP_VISUAL_FLAGS_RQD_DATA_WAVE = 1,

        /// <summary>
        /// Plugin required Spectrum data for rendering.
        /// </summary>
        AIMP_VISUAL_FLAGS_RQD_DATA_SPECTRUM = 2,

        /// <summary>
        /// Rendering must not be suspended even if the VisualDisplay window is hidden or inaccessible.
        /// </summary>
        AIMP_VISUAL_FLAGS_NOT_SUSPEND = 4
    }
}