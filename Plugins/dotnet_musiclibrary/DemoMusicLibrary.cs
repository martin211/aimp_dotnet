using System;
using System.Collections;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Extension;
using AIMP.SDK.MusicLibrary.Extension.Command;
using AIMP.SDK.MusicLibrary.Presets;

namespace dotnet_musiclibrary
{
    public class DemoMusicLibrary : 
        IAimpExtensionDataStorage, 
        IAimpDataProvider,
        //IAimpDataStorageCommandAddFiles,
        //IAimpDataStorageCommandAddFilesDialog
        IAimpExtension
    {
        private const string AIMPML_RESERVED_FIELD_ID = "ID";       // !REQUIRED! unique record id (Int32, Int64 or String)
        private const string AIMPML_RESERVED_FIELD_FILENAME = "FileName"; // !REQUIRED! string
        private const string AIMPML_RESERVED_FIELD_FILESIZE = "FileSize"; // Int64, in bytes
        private const string AIMPML_RESERVED_FIELD_DURATION = "Duration"; // double, in seconds
        private const string AIMPML_RESERVED_FIELD_USERMARK = "UserMark"; // double, 0.0 .. 5.0

        private const string EVDS_ID = AIMPML_RESERVED_FIELD_ID;
        private const string EVDS_FileName = AIMPML_RESERVED_FIELD_FILENAME;
        private const string EVDS_FileFormat = "FileFormat";
        private const string EVDS_FileAccessTime = "FileAccessTime";
        private const string EVDS_FileCreationTime = "FileCreationTime";
        private const string EVDS_FileSize = "FileSize";
        private const string EVDS_Fake = "Fake";

        public string Id => "AimpDemoMusicLibrary";

        public string Caption => "Demo ML";

        public CapabilitiesType Capabilities => CapabilitiesType.AIMPML_DATASTORAGE_CAP_FILTERING | CapabilitiesType.AIMPML_DATASTORAGE_CAP_GROUPINGPRESETS | CapabilitiesType.AIMPML_DATASTORAGE_CAP_PREIMAGES;

        public void Initialize(IAimpDataStorageManager manager)
        {
            
        }

        public void Dispose()
        {
            
        }

        public void FlushCache()
        {
            
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
            switch (schemaType)
            {
                case SchemaType.AIMPML_FIELDS_SCHEMA_ALL:
                    list = new List<IAimpDataField>
                    {
                        new AimpDataField(EVDS_ID, AimpDataFieldType.AIMPML_FIELDTYPE_STRING, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_INTERNAL | AimpDataFieldFlagsType.AIMPML_FIELDFLAG_FILTERING),
                        new AimpDataField(EVDS_FileName, AimpDataFieldType.None, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_FILTERING),
                        new AimpDataField(EVDS_FileFormat, AimpDataFieldType.AIMPML_FIELDTYPE_STRING, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_FILTERING),
                        new AimpDataField(EVDS_FileSize, AimpDataFieldType.AIMPML_FIELDTYPE_FILESIZE, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_FILTERING),
                        new AimpDataField(EVDS_FileAccessTime, AimpDataFieldType.AIMPML_FIELDTYPE_DATETIME, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_FILTERING),
                        new AimpDataField(EVDS_FileCreationTime, AimpDataFieldType.AIMPML_FIELDTYPE_DATETIME, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_FILTERING),
                        new AimpDataField(EVDS_Fake, AimpDataFieldType.AIMPML_FIELDTYPE_FILENAME, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_INTERNAL | AimpDataFieldFlagsType.AIMPML_FIELDFLAG_GROUPING)
                    };
                    break;

                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_GROUPBY:
                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_GROUPDETAILS:
                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_GROUPDETAILS:
                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT:
                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS:
                    list = new List<string>
                    {
                        EVDS_FileFormat,
                        EVDS_FileName,
                        EVDS_FileSize,
                        EVDS_FileAccessTime,
                        EVDS_FileCreationTime
                    };
                    break;

                default:
                    list = new List<string>();
                    break;
            }

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets)
        {
            if (schema == GroupingPresetsSchemaType.AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
            {
                IAimpGroupingPresetStandard preset;
                presets.Add("Demo.ExplorerView.GroupingPreset.Default", "Demo preset", EVDS_Fake, out preset);
                presets.Add("Demo.ExplorerView.GroupingPreset.Default", "Demo preset2", new List<string> { EVDS_Fake }, out preset);
                var f = preset.Fields;
                //preset.Fields.Add(EVDS_Fake);
            }

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetData(IList<string> fields, IAimpDataFilter filter, out object data)
        {
            System.Diagnostics.Debugger.Break();
            data = null;
            if (fields.Count == 1 && fields[0].ToString() == EVDS_Fake)
            {
                
            }

            return AimpActionResult.Ok;
        }

        #region Implementation of IAimpDataStorageCommandAddFiles

        public AimpActionResult Add(IList<string> files)
        {
            return AimpActionResult.Ok;
        }

        #endregion

        #region Implementation of IAimpDataStorageCommandAddFilesDialog

        public AimpActionResult Execute(IntPtr ownerHandle)
        {
            return AimpActionResult.Ok;
        }

        #endregion
    }
}