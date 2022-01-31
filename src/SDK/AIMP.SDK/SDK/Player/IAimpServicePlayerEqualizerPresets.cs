using AIMP.SDK.Player.Objects;

namespace AIMP.SDK.Player
{
    /// <summary>
    /// Provide access to presets library.
    /// </summary>
    public interface IAimpServicePlayerEqualizerPresets
    {
        /// <summary>
        /// Adds the new preset.
        /// </summary>
        /// <param name="name">The preset name.</param>
        /// <returns></returns>
        AimpActionResult<IAimpEqualizerPreset> Add(string name);

        /// <summary>
        /// Finds the preet by name.
        /// </summary>
        /// <param name="name">The preset name.</param>
        /// <returns></returns>
        AimpActionResult<IAimpEqualizerPreset> FindByName(string name);

        /// <summary>
        /// Deletes the specified preset.
        /// </summary>
        /// <param name="preset">The preset.</param>
        /// <returns></returns>
        AimpActionResult Delete(IAimpEqualizerPreset preset);

        /// <summary>
        /// Deletes the preset by index.
        /// </summary>
        /// <param name="index">The preset index.</param>
        /// <returns></returns>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Gets the preset by index.
        /// </summary>
        /// <param name="index">The preset index.</param>
        /// <returns></returns>
        AimpActionResult<IAimpEqualizerPreset> GetPreset(int index);

        /// <summary>
        /// Gets the preset count.
        /// </summary>
        /// <returns></returns>
        int GetPresetCount();
    }
}
