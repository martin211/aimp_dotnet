using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace Aimp.MusicLibraryPlugin.ExplorerMusicProvider
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
            var count = selection.GetCount();

            if (count > 0)
            {
                var r = selection.GetValue(0);
                if (r.ResultType == ActionResultType.OK)
                {
                    return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.OK);
                }
            }

            IAimpGroupingTreeDataProviderSelection data = new CustomAimpGroupingTreeDataProviderSelection();

            return new AimpActionResult<IAimpGroupingTreeDataProviderSelection>(ActionResultType.OK, data);
        }

        public AimpActionResult<string> GetFieldForAlphabeticIndex()
        {
            return new AimpActionResult<string>(ActionResultType.OK, "Test");
        }
    }
}
