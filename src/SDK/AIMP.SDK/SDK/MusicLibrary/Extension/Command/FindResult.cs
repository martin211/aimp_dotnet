using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.Objects;

namespace AIMP.SDK.MusicLibrary.Extension.Command;

public class FindResult
{
    public IAimpString GroupingPresetID { get; set; }

    public IAimpGroupingTreeSelection GroupingTreeSelection { get; set; }
}