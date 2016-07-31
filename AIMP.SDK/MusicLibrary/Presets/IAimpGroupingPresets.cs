using System.Collections.Generic;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.SDK.MusicLibrary.Presets
{
    /// <summary>
    /// Allow access to preset for data storage.
    /// </summary>
    public interface IAimpGroupingPresets
    {
        AimpActionResult Add(string id, string name, IAimpGroupingTreeDataProvider provider, out IAimpGroupingPresets preset);

        AimpActionResult Add(string id, string name, IEnumerable<string> fieldNames, out IAimpGroupingPresetStandard preset);

        AimpActionResult Add(string id, string name, string fieldName, out IAimpGroupingPresetStandard preset);

        void BeginUpdate();

        void EndUpdate();

        AimpActionResult Delete(int index);

        //AimpActionResult Get(int index, out object obj);

        //AimpActionResult GetById(string id, out object obj);

        int GetCount();
    }
}