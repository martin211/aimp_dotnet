using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace dotnet_musiclibrary
{
    public class CustomAimpGroupingTreeDataProvider : IAimpGroupingTreeDataProvider
    {
        public AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection)
        {
            throw new System.NotImplementedException();
        }

        public CapabilitiesFlags GetCapabilities()
        {
            throw new System.NotImplementedException();
        }

        public AimpActionResult GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data)
        {
            throw new System.NotImplementedException();
        }

        public AimpActionResult GetFieldForAlphabeticIndex(string fileName)
        {
            throw new System.NotImplementedException();
        }
    }
}