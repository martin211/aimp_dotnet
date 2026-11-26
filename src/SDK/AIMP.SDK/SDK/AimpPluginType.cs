namespace AIMP.SDK;

/// <summary>
/// Enum AimpPluginType
/// </summary>
public enum AimpPluginType
{
    /// <summary>
    /// The addons
    /// </summary>
    Addons = 0x1,

    /// <summary>
    /// The decoders
    /// </summary>
    Decoders = 0x2,

    /// <summary>
    /// The visuals
    /// </summary>
    Visuals = 0x4,

    /// <summary>
    /// The DSP
    /// </summary>
    DSP = 0x8,

    /// <summary>
    /// The encoders (AIMP 6.0+)
    /// </summary>
    Encoder = 0x10
}