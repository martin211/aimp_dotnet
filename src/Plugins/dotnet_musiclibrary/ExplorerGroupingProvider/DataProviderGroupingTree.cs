﻿// ----------------------------------------------------
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
        private readonly IDictionary<DataStorageCategoryType, Func<string, DataProviderGroupingTreeData>>
            _dataProviders;

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
                filter.Operation = FilterGroupOperationType.And;
                for (var i = 0; i < selection.GetCount(); i++)
                {
                    var selectionResult = selection.GetValue(i);
                    if (selectionResult.ResultType == ActionResultType.OK)
                    {
                        string fName = selectionResult.Item1;
                        object fValue = selectionResult.Item2;

                        IAimpDataFieldFilter fFilter;
                        fValue = fValue.ToString()
                            .Replace($"MyComputer\\{DataStorageCategoryType.LocalDisks}\\", string.Empty)
                            .Replace($"MyComputer\\{DataStorageCategoryType.Other}\\", string.Empty);
                        var result = filter.Add(fName, fValue, null, FieldFilterOperationType.Equals);
                        fFilter = result.Result;
                    }
                }
            }
            finally
            {
                filter.EndUpdate();
            }

            return new AimpActionResult(ActionResultType.OK);
        }

        public CapabilitiesFlags GetCapabilities()
        {
            return CapabilitiesFlags.HideAllData | CapabilitiesFlags.DontSort;
        }

        public AimpActionResult<IAimpGroupingTreeDataProviderSelection> GetData(IAimpGroupingTreeSelection selection)
        {
            IAimpGroupingTreeDataProviderSelection data = null;

            var valueResult = selection.GetValue(0);

            if (valueResult.ResultType == ActionResultType.OK)
            {
                try
                {
                    object outValue = valueResult.Item2;

                    if (!string.IsNullOrWhiteSpace(outValue?.ToString()))
                    {
                        var pathParts = outValue.ToString().Split(new[] {"\\"}, StringSplitOptions.RemoveEmptyEntries);
                        var category =
                            (DataStorageCategoryType) Enum.Parse(typeof(DataStorageCategoryType), pathParts[1]);
                        data = new DataProviderGroupingTreeSelection(_dataProviders[category](outValue.ToString()));
                        return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.OK, data);
                    }
                }
                catch (Exception)
                {
                    return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.Fail, null);
                }
            }

            data = new DataProviderGroupingTreeSelection(PopulateRoot());

            return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.OK, data);
        }

        public AimpActionResult<string> GetFieldForAlphabeticIndex()
        {
            return new AimpActionResult<string>(ActionResultType.OK, string.Empty);
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
                    ImageIndex = (int) ImageType.Folder,
                    DisplayValue = "LocalDisks"
                },
                new DataProviderGroupingTreeNode
                {
                    Standalone = true,
                    Value = $"MyComputer\\{DataStorageCategoryType.Other}",
                    HasChildren = false,
                    ImageIndex = (int) ImageType.Folder,
                    DisplayValue = "Other"
                }
            };
        }

        private DataProviderGroupingTreeData PopulateMyComputer(string data)
        {
            var result = new DataProviderGroupingTreeData();

            var pathParts = data.Split(new[] {"\\"}, StringSplitOptions.RemoveEmptyEntries);
            if (pathParts.Length <= 2)
            {
                var drivers = DriveInfo.GetDrives().Where(c => c.DriveType == DriveType.Fixed).ToList();
                result.AddRange(drivers.Select(driver => new DataProviderGroupingTreeNode
                {
                    ImageIndex = (int) ImageType.Folder,
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
                    .Where(dir =>
                        dir.Attributes.HasFlag(FileAttributes.Directory) &&
                        !(dir.Attributes.HasFlag(FileAttributes.Hidden) ||
                          dir.Attributes.HasFlag(FileAttributes.System)))
                    .Select(dir => new DataProviderGroupingTreeNode
                    {
                        DisplayValue = dir.Name,
                        Value = $"{(data.EndsWith("\\") ? data : data + "\\")}{dir.Name}\\",
                        HasChildren = dir.GetDirectories().Any(),
                        Standalone = true,
                        ImageIndex = (int) ImageType.Folder
                    }));
            }

            return result;
        }

        private DataProviderGroupingTreeData PopulateNetwork(string data)
        {
            return new DataProviderGroupingTreeData();
        }

        private ActionResultType LogResult(ActionResultType actionResult)
        {
            System.Diagnostics.Debug.WriteLine(actionResult);
            return actionResult;
        }
    }
}
