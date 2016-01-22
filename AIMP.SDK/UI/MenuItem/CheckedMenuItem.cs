namespace AIMP.SDK.UI.MenuItem
{
    using AIMP.SDK.MenuManager;

    /// <summary>
    /// Base abstract class for UI items with checked functionality.
    /// </summary>
    public abstract class CheckedMenuItem : MenuItem
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CheckedMenuItem"/> class.
        /// </summary>
        /// <param name="text">The text.</param>
        protected CheckedMenuItem(string text)
        {
            Name = text;
            Style = AimpMenuItemStyle.CheckBox;
        }
    }
}