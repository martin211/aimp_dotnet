// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
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
        RQDDataWave = 1,

        /// <summary>
        /// Plugin required Spectrum data for rendering.
        /// </summary>
        RQDDataSpectrum = 2,

        /// <summary>
        /// Rendering must not be suspended even if the VisualDisplay window is hidden or inaccessible.
        /// </summary>
        NotSuspend = 4
    }
}