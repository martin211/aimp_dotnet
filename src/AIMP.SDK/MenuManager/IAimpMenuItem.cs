namespace AIMP.SDK.MenuManager
{
    using System;
    using System.Drawing;

    using AIMP.SDK.ActionManager;

    public enum AimpMenuItemStyle
    {
        Normal,
        CheckBox,
        RadioBox
    }

    /// <summary>
    /// AIMP menu item interface.
    /// </summary>
    public interface IAimpMenuItem : IAimpActionEvent
    {
        string Custom { get; set; }

        IAimpAction Action { get; set; }

        string Id { get; set; }

        string Name { get; set; }

        bool Checked { get; set; }

        bool Enabled { get; set; }

        event EventHandler OnShow;

        Bitmap Glyph { get; set; }

        IAimpMenuItem Parent { get; set; }

        AimpMenuItemStyle Style { get; set; }

        bool Visible { get; set; }

        /// <summary>
        /// Deletes the children.
        /// </summary>
        AimpActionResult DeleteChildren();
    }
}