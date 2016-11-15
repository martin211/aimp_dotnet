using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using AIMP.DotNet.MusicLibrary.ExplorerGroupingProvider;
using AIMP.DotNet.MusicLibrary.ExplorerMusicProvider;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Extension;
using AIMP.SDK.MusicLibrary.Presets;
using AIMP.SDK.Player;

namespace AIMP.DotNet.MusicLibrary
{
    public class DemoMusicLibrary :
        IAimpExtensionDataStorage,
        IAimpDataProvider,
        //IAimpDataStorageCommandAddFiles,
        //IAimpDataStorageCommandAddFilesDialog
        IAimpExtension
    {
        public const string AIMPML_RESERVED_FIELD_ID = "ID";       // !REQUIRED! unique record id (Int32, Int64 or String)
        public const string AIMPML_RESERVED_FIELD_FILENAME = "FileName"; // !REQUIRED! string
        public const string AIMPML_RESERVED_FIELD_FILESIZE = "FileSize"; // Int64, in bytes
        public const string AIMPML_RESERVED_FIELD_DURATION = "Duration"; // double, in seconds
        public const string AIMPML_RESERVED_FIELD_USERMARK = "UserMark"; // double, 0.0 .. 5.0

        public const string EVDS_ID = AIMPML_RESERVED_FIELD_ID;
        public const string EVDS_FileName = AIMPML_RESERVED_FIELD_FILENAME;
        public const string EVDS_FileFormat = "FileFormat";
        public const string EVDS_FileAccessTime = "FileAccessTime";
        public const string EVDS_FileCreationTime = "FileCreationTime";
        public const string EVDS_FileSize = "FileSize";
        public const string EVDS_Fake = "Fake";
        public const string FieldNode = "Node";

        public string Id => "AimpDemoMusicLibrary";

        public string Caption => "Explorer media library";

        private AsyncOperation _asyncOperation;

        private DataProviderGroupingTreeData _data = new DataProviderGroupingTreeData();

        public CapabilitiesType Capabilities => CapabilitiesType.AIMPML_DATASTORAGE_CAP_FILTERING | CapabilitiesType.AIMPML_DATASTORAGE_CAP_GROUPINGPRESETS | CapabilitiesType.AIMPML_DATASTORAGE_CAP_PREIMAGES | CapabilitiesType.AIMPML_DATASTORAGE_CAP_FILTERING;

        public DemoMusicLibrary(IAimpPlayer aimpPlayer)
        {
        }

        void IAimpExtensionDataStorage.Initialize(IAimpDataStorageManager manager)
        {
        }

        void IAimpExtensionDataStorage.Terminate()
        {
        }

        void IAimpExtensionDataStorage.FlushCache()
        {
            
        }

        AimpActionResult IAimpExtensionDataStorage.ConfigLoad(IAimpConfig config, string section)
        {
            return AimpActionResult.Ok;
        }

        AimpActionResult IAimpExtensionDataStorage.ConfigSave(IAimpConfig config, string section)
        {
            return AimpActionResult.Ok;
        }

        AimpActionResult IAimpExtensionDataStorage.GetFields(SchemaType schemaType, out IList list)
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
                        new AimpDataField(EVDS_Fake, AimpDataFieldType.AIMPML_FIELDTYPE_FILENAME, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_INTERNAL | AimpDataFieldFlagsType.AIMPML_FIELDFLAG_GROUPING),
                        new AimpDataField(FieldNode, AimpDataFieldType.AIMPML_FIELDTYPE_STRING, AimpDataFieldFlagsType.AIMPML_FIELDFLAG_INTERNAL)
                        {
                            Image = ImageType.AIMPML_FIELDIMAGE_NOTE
                        }
                    };

                    return AimpActionResult.Ok;

                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_DEFAULT:
                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_VIEW_ALBUMTHUMBNAILS:
                case SchemaType.AIMPML_FIELDS_SCHEMA_TABLE_GROUPDETAILS:
                    list = new List<string>
                    {
                        EVDS_FileFormat,
                        EVDS_FileName,
                        EVDS_FileSize,
                        EVDS_FileAccessTime,
                        EVDS_FileCreationTime
                    };
                    return AimpActionResult.Ok;

                default:
                    list = new List<string>();
                    break;
            }

            return AimpActionResult.Ok;
        }

        AimpActionResult IAimpExtensionDataStorage.GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets)
        {
            if (schema == GroupingPresetsSchemaType.AIMPML_GROUPINGPRESETS_SCHEMA_BUILTIN)
            {
                IAimpGroupingPreset outPreset;
                presets.Add("AIMP.DEMO.ML.DEFAULT", "Grouping preset", new DataProviderGroupingTree(_data), out outPreset);
            }
            else if (schema == GroupingPresetsSchemaType.AIMPML_GROUPINGPRESETS_SCHEMA_DEFAULT)
            {
                IAimpGroupingPresetStandard preset;
                presets.Add("Demo.ExplorerView.GroupingPreset.Default", "Demo preset", EVDS_Fake, out preset);
            }

            return AimpActionResult.Ok;
        }

        AimpActionResult IAimpDataProvider.GetData(IList<string> fields, IAimpDataFilter filter, out object data)
        {
            string s;
            if (fields.Count == 1 && fields[0] == EVDS_Fake)
            {
                if (GetRootPath(filter, out s))
                {
                    data = new TDemoExplorerViewGroupingTreeFoldersProvider(s);
                }
                else
                {
                    data = new TDemoExplorerViewGroupingTreeDrivesProvider();
                }
            }
            else
            {
                if (GetRootPath(filter, out s))
                {
                    data = new TDemoExplorerViewDataProviderSelection(s, fields);
                }
                else
                {
                    data = "No data";
                }
            }
            //data = new RootDataProviderSelection(fields, filter, _data);

            return AimpActionResult.Ok;
        }

        private bool GetRootPath(IAimpDataFilter filter, out string str)
        {
            var s = string.Empty;
            str = string.Empty;

            var result = EnumDataFieldFilters(filter, fieldFilter =>
            {
                var res = fieldFilter.Field == EVDS_Fake;
                res = res &
                      (fieldFilter.Operation == FieldFilterOperationType.AIMPML_FIELDFILTER_OPERATION_BEGINSWITH ||
                       fieldFilter.Operation == FieldFilterOperationType.AIMPML_FIELDFILTER_OPERATION_EQUALS);

                s = fieldFilter.Value1.ToString();
                return res;
            });

            if (result)
            {
                str = s;
            }

            return result;
        }

        private bool EnumDataFieldFilters(IAimpDataFilterGroup filter, Func<IAimpDataFieldFilter, bool> aProc)
        {
            var result = false;

            if (filter != null)
            {
                for (var i = 0; i < filter.GetChildCount(); i++)
                {
                    IAimpDataFilterGroup group;
                    IAimpDataFieldFilter field;
                    if (filter.GetChild(i, out group) == AimpActionResult.Ok && group != null)
                    {
                        result = EnumDataFieldFilters(group, aProc);
                    }
                    else if (filter.GetChild(i, out field) == AimpActionResult.Ok && field != null)
                    {
                        result = aProc(field);
                    }

                    if (result)
                    {
                        break;
                    }
                }
            }

            return result;
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