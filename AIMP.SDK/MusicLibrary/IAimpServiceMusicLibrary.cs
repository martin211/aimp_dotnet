using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.SDK.MusicLibrary
{
    public interface IAimpServiceMusicLibrary
    {
        AimpActionResult GetActiveDataStorage(out IAimpDataStorage dataStorage);

        AimpActionResult GeteActiveGroupingPreset(out IAimpGroupingPresets preset);

        AimpActionResult SetActiveStorage(IAimpDataStorage storage);

        //AimpActionResult GetStorage(int index, StorageType storageType, out object obj);

        //AimpActionResult GetStorageById(string id, StorageType storageType, out object obj);

        int GetStorageCount();
    }
}