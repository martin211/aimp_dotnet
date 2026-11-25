namespace AIMP.SDK.MusicLibrary.DataStorage;

/// <summary>
/// AIMP 6.0 name for the grouping tree selection iteration step.
/// </summary>
public interface IAimpGroupingTreeDataProviderSelection2 : IAimpGroupingTreeDataProviderSelection
{
    /// <summary>
    /// Jumps to the next row. Returns false if the current row is the last.
    /// </summary>
    bool NextRow();
}