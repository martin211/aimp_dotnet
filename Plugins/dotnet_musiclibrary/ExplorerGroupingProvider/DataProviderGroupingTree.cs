using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using AIMP.DotNet.MusicLibrary.ExplorerMusicProvider;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

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
                        var category = (DataStorageCategoryType) Enum.Parse(typeof(DataStorageCategoryType), outValue.ToString().Split(new []{ "\\"}, StringSplitOptions.RemoveEmptyEntries)[1]);
                        data = new DataProviderGroupingTreeSelection(_dataProviders[category](outFieldName));
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
                    HasChildren = true,
                    ImageIndex = (int) ImageType.AIMPML_FIELDIMAGE_FOLDER,
                    DisplayValue = "Other"
                }
            };
        }

        private DataProviderGroupingTreeData PopulateMyComputer(string data)
        {
            var drivers = DriveInfo.GetDrives().Where(c => c.DriveType == DriveType.Fixed).ToList();

            var result = new DataProviderGroupingTreeData();
            result.AddRange(drivers.Select(driver => new DataProviderGroupingTreeNode
            {
                ImageIndex = (int)ImageType.AIMPML_FIELDIMAGE_FOLDER,
                Standalone = true,
                HasChildren = true,
                DisplayValue = driver.Name,
                Value = $"MyComputer\\{DataStorageCategoryType.LocalDisks}\\{driver.Name.Replace(":\\", string.Empty)}"
            }));

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