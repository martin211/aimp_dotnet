// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Collections;
using System.Collections.Generic;
using AIMP.DotNet.MusicLibrary.ExplorerGroupingProvider;
using AIMP.DotNet.MusicLibrary.ExplorerMusicProvider;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Extension;
using AIMP.SDK.MusicLibrary.Extension.Command;
using AIMP.SDK.MusicLibrary.Presets;
using AIMP.SDK.Player;

namespace AIMP.DotNet.MusicLibrary
{
    public class DemoMusicLibrary :
        IAimpExtensionDataStorage,
        IAimpDataProvider,
        IAimpExtension,
        IAimpDataStorageCommandAddFiles,
        IAimpDataStorageCommandAddFilesDialog,
        IAimpDataStorageCommandDeleteFiles,
        IAimpDataStorageCommandDropData,
        IAimpDataStorageCommandReloadTags,
        IAimpDataStorageCommandReportDialog,
        IAimpDataStorageCommandUserMark
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
        private readonly IAimpPlayer _aimpPlayer;

        private readonly DataProviderGroupingTreeData _data = new DataProviderGroupingTreeData();
        IAimpGroupingPresetStandard _groupingPresetStandard;

        private IAimpGroupingPreset _outPreset;

        public DemoMusicLibrary(IAimpPlayer aimpPlayer)
        {
            _aimpPlayer = aimpPlayer;
        }

        AimpActionResult<object> IAimpDataProvider.GetData(IList<string> fields, IAimpDataFilter filter)
        {
            object data = null;
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

            return new AimpActionResult<object>(ActionResultType.OK, data);
        }

        #region Implementation of IAimpDataStorageCommandAddFiles

        public AimpActionResult Add(IList<string> files)
        {
            System.Diagnostics.Debug.WriteLine("IAimpDataStorageCommandAddFiles.Add");
            return new AimpActionResult(ActionResultType.OK);
        }

        #endregion

        #region Implementation of IAimpDataStorageCommandAddFilesDialog

        AimpActionResult IAimpDataStorageCommandAddFilesDialog.Execute(IntPtr ownerHandle)
        {
            System.Diagnostics.Debug.WriteLine($"IAimpDataStorageCommandAddFilesDialog.Execute: {ownerHandle}");
            return new AimpActionResult(ActionResultType.OK);
        }

        #endregion

        public bool CanDelete(bool physically)
        {
            System.Diagnostics.Debug.WriteLine("IAimpDataStorageCommandDeleteFiles.CanDelete");
            return true;
        }

        public AimpActionResult Delete(IAimpFileList files, bool physically)
        {
            System.Diagnostics.Debug.WriteLine("IAimpDataStorageCommandDeleteFiles.Delete");
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult DropData()
        {
            System.Diagnostics.Debug.WriteLine("IAimpDataStorageCommandDropData.DropData");
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult ReloadTags(IAimpFileList files)
        {
            System.Diagnostics.Debug.WriteLine("IAimpDataStorageCommandReloadTags.ReloadTags");
            return new AimpActionResult(ActionResultType.OK);
        }

        //public ActionResultType Execute(IntPtr ownerHandle)
        //{
        //    System.Diagnostics.Debug.WriteLine($"IAimpDataStorageCommandReportDialog.Execute: {ownerHandle}");
        //    return ActionResultType.OK;
        //}
        AimpActionResult IAimpDataStorageCommandReportDialog.Execute(IntPtr ownerHandle)
        {
            System.Diagnostics.Debug.WriteLine($"IAimpDataStorageCommandReportDialog.Execute: {ownerHandle}");
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult SetMark(object id, double value)
        {
            System.Diagnostics.Debug.WriteLine($"IAimpDataStorageCommandUserMark.SetMark: {id} {value}");
            return new AimpActionResult(ActionResultType.OK);
        }

        public string Id => "AimpDemoMusicLibrary";

        public string Caption => "Explorer media library";

        public CapabilitiesType Capabilities => CapabilitiesType.Filtering | CapabilitiesType.GroupingPresets | CapabilitiesType.Preimages | CapabilitiesType.Filtering;

        void IAimpExtensionDataStorage.Initialize(IAimpDataStorageManager manager)
        {
        }

        void IAimpExtensionDataStorage.Terminate()
        {
            _groupingPresetStandard = null;
            _outPreset = null;
        }

        void IAimpExtensionDataStorage.FlushCache()
        {
            
        }

        AimpActionResult IAimpExtensionDataStorage.ConfigLoad(IAimpConfig config, string section)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        AimpActionResult IAimpExtensionDataStorage.ConfigSave(IAimpConfig config, string section)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        AimpActionResult<IList> IAimpExtensionDataStorage.GetFields(SchemaType schemaType)
        {
            IList list = null;
            switch (schemaType)
            {
                case SchemaType.All:
                    list = new List<IAimpDataField>
                    {
                        new AimpDataField(EVDS_ID, AimpDataFieldType.String, AimpDataFieldFlagsType.Internal | AimpDataFieldFlagsType.Filtering),
                        new AimpDataField(EVDS_FileName, AimpDataFieldType.None, AimpDataFieldFlagsType.Filtering),
                        new AimpDataField(EVDS_FileFormat, AimpDataFieldType.String, AimpDataFieldFlagsType.Filtering),
                        new AimpDataField(EVDS_FileSize, AimpDataFieldType.FileSize, AimpDataFieldFlagsType.Filtering),
                        new AimpDataField(EVDS_FileAccessTime, AimpDataFieldType.DateTime, AimpDataFieldFlagsType.Filtering),
                        new AimpDataField(EVDS_FileCreationTime, AimpDataFieldType.DateTime, AimpDataFieldFlagsType.Filtering),
                        new AimpDataField(EVDS_Fake, AimpDataFieldType.FileName, AimpDataFieldFlagsType.Internal | AimpDataFieldFlagsType.Grouping),
                        new AimpDataField(FieldNode, AimpDataFieldType.String, AimpDataFieldFlagsType.Internal)
                        {
                            Image = ImageType.Note
                        }
                    };

                    return new AimpActionResult<IList>(ActionResultType.OK, list);

                case SchemaType.TableViewDefault:
                case SchemaType.TableViewAlbumThumbnails:
                case SchemaType.TableGroupDetails:
                    list = new List<string>
                    {
                        EVDS_FileFormat,
                        EVDS_FileName,
                        EVDS_FileSize,
                        EVDS_FileAccessTime,
                        EVDS_FileCreationTime
                    };
                    return new AimpActionResult<IList>(ActionResultType.OK, list);

                default:
                    list = new List<string>();
                    break;
            }

            return new AimpActionResult<IList>(ActionResultType.OK, list);
        }

        AimpActionResult IAimpExtensionDataStorage.GetGroupingPresets(GroupingPresetsSchemaType schema, IAimpGroupingPresets presets)
        {
            if (schema == GroupingPresetsSchemaType.BuiltIn)
            {
                var result = presets.Add("AIMP.DEMO.ML.DEFAULT", "Grouping preset", new DataProviderGroupingTree(_data));
                _outPreset = result.Result;
            }
            else if (schema == GroupingPresetsSchemaType.Default)
            {
                var result = presets.Add("Demo.ExplorerView.GroupingPreset.Default", "Demo preset", EVDS_Fake);
                _groupingPresetStandard = result.Result;
            }

            return new AimpActionResult(ActionResultType.OK);
        }

        private bool GetRootPath(IAimpDataFilter filter, out string str)
        {
            var s = string.Empty;
            str = string.Empty;

            var result = EnumDataFieldFilters(filter, fieldFilter =>
            {
                var res = fieldFilter.Field == EVDS_Fake || fieldFilter.Field == FieldNode;
                res = res &
                      (fieldFilter.Operation == FieldFilterOperationType.BeginsWith ||
                       fieldFilter.Operation == FieldFilterOperationType.Equals);

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
                    var getGroup = filter.GetFilterGroup(i);
                    var getField = filter.GetFieldFilter(i);
                    
                    if (getGroup.ResultType == ActionResultType.OK && getGroup.Result != null)
                    {
                        result = EnumDataFieldFilters(getGroup.Result, aProc);
                    }
                    else if (getField.ResultType == ActionResultType.OK && getField.Result != null)
                    {
                        result = aProc(getField.Result);
                    }

                    if (result)
                    {
                        break;
                    }
                }
            }

            return result;
        }
    }
}