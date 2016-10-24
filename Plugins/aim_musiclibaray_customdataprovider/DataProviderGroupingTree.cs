using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.CustomDataProvider
{
    public class DataProviderGroupingTree : IAimpGroupingTreeDataProvider
    {
        private IAimpGroupingPresets _groupingPresets;
        private readonly IDictionary<DataStorageCategoryType, Func<string, DataProviderGroupingTreeData>> _dataProviders;

        public DataProviderGroupingTree()
        {
            _dataProviders = new ConcurrentDictionary<DataStorageCategoryType, Func<string, DataProviderGroupingTreeData>>();
            _dataProviders.Add(DataStorageCategoryType.Categoty1, PopulateRoot);
            _dataProviders.Add(DataStorageCategoryType.Categoty2, PopulateCategories);
        }

        public DataProviderGroupingTree(IAimpGroupingPresets groupingPresets)
        {
            _groupingPresets = groupingPresets;
        }

        public AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            filter.BeginUpdate();
            try
            {
                string outFieldName;
                object outValue;
                IAimpDataFieldFilter outFilter;
                filter.Operation = FilterGroupOperationType.AND;
                for (var i = 0; i < selection.GetCount(); i++)
                {
                    if (selection.GetValue(i, out outFieldName, out outValue) == AimpActionResult.Ok)
                    {
                        filter.Add(outFieldName, outValue, null,
                            FieldFilterOperationType.AIMPML_FIELDFILTER_OPERATION_EQUALS, out outFilter);
                    }
                }
            }
            finally
            {
                filter.EndUpdate();
            }

            return AimpActionResult.Ok;
        }

        public CapabilitiesFlags GetCapabilities()
        {
            return CapabilitiesFlags.HideAllData | CapabilitiesFlags.DontSort;
        }

        public AimpActionResult GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data)
        {
            string outFieldName;
            object outValue;
            data = null;
            if (selection.GetValue(0, out outFieldName, out outValue) == AimpActionResult.Ok)
            {
                if (outFieldName != DataStorage.FieldNode)
                {
                    return AimpActionResult.Unexpected;
                }
            }
            else
            {
                outValue = string.Empty;
            }

            try
            {
                var category = (DataStorageCategoryType) Enum.Parse(typeof(DataStorageCategoryType), outValue.ToString());
                data = new DataProviderGroupingTreeSelection(_dataProviders[category](outFieldName));
                return AimpActionResult.Ok;
            }
            catch (Exception)
            {
                return AimpActionResult.Fail;
            }
        }

        public AimpActionResult GetFieldForAlphabeticIndex(out string fieldName)
        {
            fieldName = string.Empty;
            return AimpActionResult.NotImplemented;
        }

        private DataProviderGroupingTreeData PopulateRoot(string data)
        {
            return null;
        }

        private DataProviderGroupingTreeData PopulateCategories(string data)
        {
            return null;
        }
    }
}