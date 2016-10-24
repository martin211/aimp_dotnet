using System;
using System.Collections;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Extension;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.CustomDataProvider
{
    public class CustomDataProvider : IAimpExtensionDataStorage, IAimpDataProvider, IAimpExtension
    {
        private DataStorage _dataStorage;

        public string Id => "CustomDataProvider";

        public string Caption => "Demo Custom Data Provider";

        public CapabilitiesType Capabilities => CapabilitiesType.AIMPML_DATASTORAGE_CAP_GROUPINGPRESETS | CapabilitiesType.AIMPML_DATASTORAGE_CAP_FILTERING;

        public void Initialize(IAimpDataStorageManager manager)
        {
            _dataStorage = new DataStorage();
        }

        public void Terminate()
        {
            throw new System.NotImplementedException();
        }

        public void FlushCache()
        {
            throw new System.NotImplementedException();
        }

        public AimpActionResult ConfigLoad(IAimpConfig config, string section)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult ConfigSave(IAimpConfig config, string section)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFields(SchemaType schemaType, out IList list)
        {
            list = _dataStorage.GetFields(schemaType);
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets)
        {
            if (schema == GroupingPresetsSchemaType.AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
            {
                IAimpGroupingPreset outPreset;
                presets.Add("AIMP.DEMO.ML.DEFAULT", string.Empty, new DataProviderGroupingTree(presets), out outPreset);
            }

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetData(IList<string> fields, IAimpDataFilter filter, out object data)
        {
            throw new System.NotImplementedException();
        }
    }
}