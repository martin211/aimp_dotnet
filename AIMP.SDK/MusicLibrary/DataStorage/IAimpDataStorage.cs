using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataStorage
    {
        /// <summary>
        /// Gets the storage identifier.
        /// </summary>
        string Id { get; }

        /// <summary>
        /// Gets the storage caption.
        /// </summary>
        string Caption { get; }

        /// <summary>
        /// Gets or sets the current grouping preset.
        /// </summary>
        IAimpGroupingPreset GroupingPreset { get; set; }
    }
}