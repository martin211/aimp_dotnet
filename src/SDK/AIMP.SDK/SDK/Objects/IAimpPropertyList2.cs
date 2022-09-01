namespace AIMP.SDK.Objects;

public interface IAimpPropertyList
{
    /// <summary>
    /// Begins the update.
    /// </summary>
    void BeginUpdate();

    /// <summary>
    /// Ends the update.
    /// </summary>
    void EndUpdate();
}

public interface IAimpPropertyList2 : IAimpPropertyList
{

}