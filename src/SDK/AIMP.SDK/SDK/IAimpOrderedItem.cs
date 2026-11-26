using AIMP.SDK.MusicLibrary;
using AIMP.SDK.Objects;

namespace AIMP.SDK;

public interface IAimpOrderedItem
{
    IAimpString Name { get; }

    SortDirectionType Value { get; set; }
}