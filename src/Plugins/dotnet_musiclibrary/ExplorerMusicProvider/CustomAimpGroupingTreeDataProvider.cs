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
        public AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            return new AimpActionResult(ActionResultType.NotImplemented);
        }

        public CapabilitiesFlags GetCapabilities()
        {
            return CapabilitiesFlags.None;
        }

        public AimpActionResult<IAimpGroupingTreeDataProviderSelection> GetData(IAimpGroupingTreeSelection selection)
        {
            IAimpGroupingTreeDataProviderSelection data = null;

            var count = selection.GetCount();

            if (count > 0)
            {
                var r = selection.GetValue(0);
                if (r.ResultType == ActionResultType.OK)
                {
                    return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.OK, data);
                }
            }

            data = new CustomAimpGroupingTreeDataProviderSelection();

            return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.OK, data);
        }

        public AimpActionResult<string> GetFieldForAlphabeticIndex()
        {
            return new AimpActionResult<string>(ActionResultType.OK, "Test");
        }
    }
}
