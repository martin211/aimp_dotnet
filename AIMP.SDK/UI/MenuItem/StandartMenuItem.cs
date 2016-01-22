namespace AIMP.SDK.UI.MenuItem
{
    using AIMP.SDK.MenuManager;

    /// <summary>
    /// Standart menu item.
    /// </summary>
    public sealed class StandartMenuItem : MenuItem
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="StandartMenuItem"/> class.
        /// </summary>
        /// <param name="text">The text.</param>
        public StandartMenuItem(string text)
        {
            Name = text;
            Style = AimpMenuItemStyle.Normal;
        }
    }
}