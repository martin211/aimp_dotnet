namespace AIMP.SDK.MusicLibrary.Presets
{
    public interface IAimpGroupingPreset
    {
        /// <summary>
        /// Gets or sets the user custom data.
        /// </summary>
        string Custom { get; set; }

        /// <summary>
        /// Gets or sets the preset identifier.
        /// </summary>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the preset name.
        /// </summary>
        string Name { get; set; }
    }
}