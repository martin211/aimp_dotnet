using System;

namespace AIMP.SDK.Visuals;

/// <summary>
/// Enum AimpVisualFlags
/// </summary>
[Flags]
public enum AimpVisualFlags
{
    /// <summary>
    /// Plugin required WaveForm data for rendering.
    /// </summary>
    RQDDataWaveForm = 1,

    /// <summary>
    /// Plugin required Spectrum data for rendering.
    /// </summary>
    RQDDataSpectrum = 2,

    /// <summary>
    /// Rendering must not be suspended even if the VisualDisplay window is hidden or inaccessible.
    /// </summary>
    NotSuspend = 4,

    /// <summary>
    /// Internal use: logarithmic spectrum data.
    /// </summary>
    RQDDataLogarithmicSpectrum = 8,

    /// <summary>
    /// Receive extra actions (move, leave, down) in Action (AIMP 6.0+).
    /// </summary>
    ActionExtra = 16,

    /// <summary>
    /// Receive double-click action in Action (AIMP 6.0+).
    /// </summary>
    ActionDoubleClick = 32,

    /// <summary>
    /// Receive mouse wheel actions in Action (AIMP 6.0+).
    /// </summary>
    ActionWheel = 64
}