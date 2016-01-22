using System;
namespace AIMP.SDK.UI.MenuItem
{
    using System.Drawing;

    using AIMP.SDK.ActionManager;
    using AIMP.SDK.MenuManager;

    /// <summary>
    /// Base menu item class.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public abstract class MenuItem : IAimpMenuItem
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MenuItem"/> class.
        /// </summary>
        /// <param name="text">The text.</param>
        protected MenuItem()
        {
            Visible = true;
            Enabled = true;
            Id = $"aimp_uiitem_{GetHashCode()}";
        }

        public AimpMenuItemStyle Style { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="MenuItem"/> is visible.
        /// </summary>
        /// <value>
        ///   <c>true</c> if visible; otherwise, <c>false</c>.
        /// </value>
        public bool Visible { get; set; }

        /// <summary>
        /// Deletes the children.
        /// </summary>
        public AimpActionResult DeleteChildren()
        {
            throw new NotImplementedException();
        }

        public Bitmap Image { get; set; }

        private bool _enabled;

        public string Custom { get; set; }

        public IAimpAction Action { get; set; }

        public string Id { get; set; }

        public string Name { get; set; }

        public bool Checked { get; set; }

        public bool Enabled { get; set; }

        public event EventHandler OnExecute;

        public event EventHandler OnShow;

        public Bitmap Glyph { get; set; }

        public IAimpMenuItem Parent { get; set; }
    }
}