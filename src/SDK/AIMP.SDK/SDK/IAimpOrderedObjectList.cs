using AIMP.SDK.MusicLibrary;

namespace AIMP.SDK;

public interface IAimpOrderedObjectList : IAimpObjectList<IAimpOrderedItem>
{
    IAimpOrderedItem Create(string name, SortDirectionType sortDirection);
}