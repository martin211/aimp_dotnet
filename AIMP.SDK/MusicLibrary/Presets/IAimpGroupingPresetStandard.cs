using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.Presets
{
    public interface IAimpGroupingPresetStandard : IAimpGroupingPreset
    {
        /// <summary>
        /// Gets or sets the fields that used for groupping at filter.
        /// </summary>
        IAimpObjectList<string> Fields { get; set; }

        /// <summary>
        /// Gets the used filter.
        /// </summary>
        /// <param name="filter">The filter.</param>
        /// <returns></returns>
        AimpActionResult GetFilter(out IAimpDataFieldFilter filter);
    }
}