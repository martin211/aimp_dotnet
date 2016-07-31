using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpDataStorage
    {
        string Id { get; }

        string Caption { get; }

        IAimpGroupingPreset GroupingPreset { get; set; }
    }
}