using System.Collections.Generic;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Allow access to preset for data storage.
    /// </summary>
    public interface IAimpGroupingPresets
    {
        AimpActionResult Add(string id, string name, IAimpGroupingTreeDataProvider provider, out IAimpGroupingPreset preset);

        AimpActionResult Add(string id, string name, IList<string> fieldNames, out IAimpGroupingPresetStandard preset);

        AimpActionResult Add(string id, string name, string fieldName, out IAimpGroupingPresetStandard preset);

        void BeginUpdate();

        void EndUpdate();

        AimpActionResult Delete(int index);

        AimpActionResult Get(int index, out IAimpGroupingPreset preset);

        AimpActionResult Get(int index, out IAimpGroupingPresetStandard preset);

        AimpActionResult GetById(int index, out IAimpGroupingPreset preset);

        AimpActionResult GetById(int index, out IAimpGroupingPresetStandard preset);

        int GetCount();
    }
}