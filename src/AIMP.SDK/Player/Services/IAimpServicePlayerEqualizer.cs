using AIMP.SDK.Player.Primitives;

namespace AIMP.SDK.Player.Services
{
    /// <summary>
    /// Service provides an access to equalizer.
    /// </summary>
    public interface IAimpServicePlayerEqualizer : IAimpEqualizerBands
    {
        /// <summary>
        /// Get equalizer state (on/off).
        /// </summary>
        /// <returns>Equalizer state.</returns>
        bool GetActive();

        /// <summary>
        /// Set equalizer state (on/off).
        /// </summary>
        /// <param name="value"></param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetActive(bool value);

        /// <summary>
        /// Get preamp value.
        /// Equalizer should be enabled.
        /// </summary>
        /// <returns>Preamp value in range of -15.0 to +15.0 dB.</returns>
        AimpActionResult<double> GetPreamp();

        /// <summary>
        /// Set preamp.
        /// Equalizer should be enabled.
        /// </summary>
        /// <param name="value">Preamp value in range of -15.0 to +15.0 dB.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetPreamp(double value);

        /// <summary>
        /// Get preset,
        /// </summary>
        /// <returns>AimpActionResult</returns>
        AimpActionResult<IAimpEqualizerPreset> GetPreset();

        /// <summary>
        /// Set preset.
        /// </summary>
        /// <param name="value">Preset <see cref="IAimpEqualizerPreset"/></param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult SetPreset(IAimpEqualizerPreset value);
    }
}
