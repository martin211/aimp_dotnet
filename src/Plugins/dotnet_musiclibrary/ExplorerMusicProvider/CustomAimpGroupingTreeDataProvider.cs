// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.DotNet.MusicLibrary.ExplorerMusicProvider
{
    public class CustomAimpGroupingTreeDataProvider : IAimpGroupingTreeDataProvider
    {
        public AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            return AimpActionResult.NotImplemented;
        }

        public CapabilitiesFlags GetCapabilities()
        {
            return CapabilitiesFlags.None;
        }

        public AimpActionResult GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data)
        {
            data = null;

            string name;
            object value;

            var count = selection.GetCount();

            if (count > 0)
            {
                if (selection.GetValue(0, out name, out value) == AimpActionResult.OK)
                {
                    return AimpActionResult.OK;
                }
            }

            data = new CustomAimpGroupingTreeDataProviderSelection();

            return AimpActionResult.OK;
        }

        public AimpActionResult GetFieldForAlphabeticIndex(out string fieldName)
        {
            fieldName = "Test";
            return AimpActionResult.OK;
        }
    }
}