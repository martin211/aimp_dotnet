namespace AIMP.SDK;

/// <summary>
/// Extended object list (AIMP 6.0+).
/// </summary>
public interface IAimpObjectList2 : IAimpObjectList
{
    /// <summary>
    /// Returns the index of the item or -1 when it is not in the list.
    /// </summary>
    int IndexOf(object item);
}