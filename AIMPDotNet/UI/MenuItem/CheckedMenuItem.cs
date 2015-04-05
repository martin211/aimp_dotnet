namespace AIMP.SDK.UI.MenuItem
{
    /// <summary>
    /// Base abstract class for UI items with checked functionality.
    /// </summary>
    public abstract class CheckedMenuItem : MenuItem
    {
        private bool _checked;

        /// <summary>
        /// Initializes a new instance of the <see cref="CheckedMenuItem"/> class.
        /// </summary>
        /// <param name="text">The text.</param>
        protected CheckedMenuItem(string text)
            : base(text)
        {
            Checked = false;
            MenuItemType = MenuItemType.CheckBox;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="MenuItem"/> is checked.
        /// </summary>
        /// <value>
        ///   <c>true</c> if checked; otherwise, <c>false</c>.
        /// </value>
        public bool Checked
        {
            get
            {
                return _checked;
            }
            set
            {
                if (_checked != value)
                {
                    _checked = value;
                    OnPropertyChanged("Checked");
                }
            }
        }

        internal override void OnClick()
        {
            Checked = !Checked;
            base.OnClick();
        }
    }
}