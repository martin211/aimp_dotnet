using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary
{
    public interface IAimpServiceMusicLibrary
    {
        AimpActionResult GetActiveStorage(out IAimpDataStorage storage);

        AimpActionResult GetActiveStorage(out IAimpGroupingPresets preset);

        AimpActionResult SetActiveStorage(IAimpDataStorage storage);

        AimpActionResult SetActiveStorage(IAimpGroupingPresets preset);

        AimpActionResult GetStorage(int index, out IAimpDataStorage storage);

        AimpActionResult GetStorage(int index, out IAimpGroupingPresets preset);

        AimpActionResult GetStorageById(string id, out IAimpDataStorage storage);

        AimpActionResult GetStorageById(string id, out IAimpGroupingPresets preset);

        int GetStorageCount();
    }
}