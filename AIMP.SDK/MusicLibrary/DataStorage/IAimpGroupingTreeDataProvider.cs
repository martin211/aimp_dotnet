using System;
using System.Drawing;
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    [Flags]
    public enum CapabilitiesFlags
    {
        None = 0,
        AIMPML_GROUPINGTREEDATAPROVIDER_CAP_HIDEALLDATA,
        AIMPML_GROUPINGTREEDATAPROVIDER_CAP_DONTSORT
    }

    public interface IAimpGroupingTreeDataProvider
    {
        AimpActionResult AppendFilter(IAimpDataFilterGroup filter, IAimpGroupingTreeSelection selection);

        CapabilitiesFlags GetCapabilities();

        AimpActionResult GetData(IAimpGroupingTreeSelection selection, out IAimpGroupingTreeDataProviderSelection data);

        AimpActionResult GetFieldForAlphabeticIndex(string fileName);
    }
}