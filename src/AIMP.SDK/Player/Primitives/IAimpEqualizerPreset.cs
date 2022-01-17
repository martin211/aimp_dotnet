namespace AIMP.SDK.Player.Primitives
{
    /// <summary>
    /// Interface provides an access to the equalizer preset.
    /// </summary>
    public interface IAimpEqualizerPreset : IAimpEqualizerBands
    {
        /// <summary>
        /// Gets the name.
        /// </summary>
        /// <returns></returns>
        StringActionResult GetName();

        /// <summary>
        /// Sets the name.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <returns></returns>
        AimpActionResult SetName(IAimpString value);
    }
}