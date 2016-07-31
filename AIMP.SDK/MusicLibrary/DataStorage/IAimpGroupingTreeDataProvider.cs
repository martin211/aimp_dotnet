using System;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    public interface IAimpGroupingTreeDataProvider
    {
        //AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection);

        CapabilitiesFlags GetCapabilities();
    }
}