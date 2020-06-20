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

using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.DotNet.MusicLibrary.ExplorerMusicProvider
{
    public class CustomAimpGroupingTreeDataProvider : IAimpGroupingTreeDataProvider
    {
        public ActionResultType AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            return ActionResultType.NotImplemented;
        }

        public CapabilitiesFlags GetCapabilities()
        {
            return CapabilitiesFlags.None;
        }

        public ActionResultType GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data)
        {
            data = null;

            string name;
            object value;

            var count = selection.GetCount();

            if (count > 0)
            {
                if (selection.GetValue(0, out name, out value) == ActionResultType.OK)
                {
                    return ActionResultType.OK;
                }
            }

            data = new CustomAimpGroupingTreeDataProviderSelection();

            return ActionResultType.OK;
        }

        public ActionResultType GetFieldForAlphabeticIndex(out string fieldName)
        {
            fieldName = "Test";
            return ActionResultType.OK;
        }
    }
}