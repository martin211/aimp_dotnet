namespace AIMP.SDK.MenuManager
{
    /// <summary>
    /// AIMP menu item interface.
    /// </summary>
    public interface IAimpMenuItem : IAimpPropertyList
    {
        /// <summary>
        /// Deletes the children.
        /// </summary>
        void DeleteChildren();
    }
}