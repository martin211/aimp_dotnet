using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.DotNet.MusicLibrary.ExplorerGroupingProvider
{
    public enum DataStorageCategoryType
    {
        Root,
        LocalDisks,
        Other
    }

    public class DataProviderGroupingTree : IAimpGroupingTreeDataProvider
    {
        private readonly IDictionary<DataStorageCategoryType, Func<string, DataProviderGroupingTreeData>> _dataProviders;

        public DataProviderGroupingTree()
        {
            _dataProviders = new Dictionary<DataStorageCategoryType, Func<string, DataProviderGroupingTreeData>>();
            _dataProviders.Add(DataStorageCategoryType.LocalDisks, PopulateMyComputer);
            _dataProviders.Add(DataStorageCategoryType.Other, PopulateNetwork);
        }

        public DataProviderGroupingTree(DataProviderGroupingTreeData data)
            : this()
        {
        }

        public AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            filter.BeginUpdate();
            try
            {
                filter.Operation = FilterGroupOperationType.AND;
                for (var i = 0; i < selection.GetCount(); i++)
                {
                    string fName;
                    object fValue;
                    if (selection.GetValue(i, out fName, out fValue) == AimpActionResult.Ok)
                    {
                        IAimpDataFieldFilter fFilter;
                        fValue = fValue.ToString()
                            .Replace($"MyComputer\\{DataStorageCategoryType.LocalDisks}\\", string.Empty)
                            .Replace($"MyComputer\\{DataStorageCategoryType.Other}\\", string.Empty);
                        filter.Add(fName, fValue, null, FieldFilterOperationType.AIMPML_FIELDFILTER_OPERATION_EQUALS, out fFilter);
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

            if (LogResult(selection.GetValue(0, out outFieldName, out outValue)) == AimpActionResult.Ok)
            {
                try
                {
                    if (!string.IsNullOrWhiteSpace(outValue?.ToString()))
                    {
                        var pathParts = outValue.ToString().Split(new[] {"\\"}, StringSplitOptions.RemoveEmptyEntries);
                        var category = (DataStorageCategoryType) Enum.Parse(typeof(DataStorageCategoryType), pathParts[1]);
                        data = new DataProviderGroupingTreeSelection(_dataProviders[category](outValue.ToString()));
                        return AimpActionResult.Ok;
                    }
                }
                catch (Exception)
                {
                    return AimpActionResult.Fail;
                }
            }

            data = new DataProviderGroupingTreeSelection(PopulateRoot());

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFieldForAlphabeticIndex(out string fieldName)
        {
            System.Diagnostics.Debug.WriteLine("GetFieldForAlphabeticIndex");
            fieldName = string.Empty;
            return AimpActionResult.Ok;
        }

        private DataProviderGroupingTreeData PopulateRoot()
        {
            return new DataProviderGroupingTreeData
            {
                new DataProviderGroupingTreeNode
                {
                    Standalone = true,
                    Value = $"MyComputer\\{DataStorageCategoryType.LocalDisks}",
                    HasChildren = true,
                    ImageIndex = (int) ImageType.AIMPML_FIELDIMAGE_FOLDER,
                    DisplayValue = "LocalDisks"
                },
                new DataProviderGroupingTreeNode
                {
                    Standalone = true,
                    Value = $"MyComputer\\{DataStorageCategoryType.Other}",
                    HasChildren = false,
                    ImageIndex = (int) ImageType.AIMPML_FIELDIMAGE_FOLDER,
                    DisplayValue = "Other"
                }
            };
        }

        private DataProviderGroupingTreeData PopulateMyComputer(string data)
        {
            var result = new DataProviderGroupingTreeData();

            var pathParts = data.Split(new[] { "\\" }, StringSplitOptions.RemoveEmptyEntries);
            if (pathParts.Length <= 2)
            {
                var drivers = DriveInfo.GetDrives().Where(c => c.DriveType == DriveType.Fixed).ToList();
                result.AddRange(drivers.Select(driver => new DataProviderGroupingTreeNode
                {
                    ImageIndex = (int) ImageType.AIMPML_FIELDIMAGE_FOLDER,
                    Standalone = true,
                    HasChildren = true,
                    DisplayValue = driver.Name,
                    Value = $"MyComputer\\{DataStorageCategoryType.LocalDisks}\\{driver.Name}"
                }));
            }
            else
            {
                var path = data.Replace($"MyComputer\\{DataStorageCategoryType.LocalDisks}\\", string.Empty);
                DirectoryInfo di = new DirectoryInfo(path);
                result.AddRange(di.GetDirectories()
                    .Where(dir => dir.Attributes.HasFlag(FileAttributes.Directory) && !(dir.Attributes.HasFlag(FileAttributes.Hidden) || dir.Attributes.HasFlag(FileAttributes.System)))
                    .Select(dir => new DataProviderGroupingTreeNode
                    {
                        DisplayValue = dir.Name,
                        Value = $"{(data.EndsWith("\\") ? data : data + "\\" )}{dir.Name}\\",
                        HasChildren = dir.GetDirectories().Any(),
                        Standalone = true,
                        ImageIndex = (int)ImageType.AIMPML_FIELDIMAGE_FOLDER
                    }));
            }

            return result;
        }

        private DataProviderGroupingTreeData PopulateNetwork(string data)
        {
            return new DataProviderGroupingTreeData();
        }

        private AimpActionResult LogResult(AimpActionResult actionResult)
        {
            System.Diagnostics.Debug.WriteLine(actionResult);
            return actionResult;
        }
    }
}