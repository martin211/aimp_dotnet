using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Represents the preset for standard grouping.
    /// </summary>
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
        /// <returns>Operation result <seealso cref="AimpActionResult"/></returns>
        AimpActionResult GetFilter(out IAimpDataFilterGroup filter);
    }
}