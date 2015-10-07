using System;
using AIMP.SDK.Services.MenuManager;

namespace AIMP.SDK.UI.MenuItem
{
    using System.Drawing;

    internal delegate void SubMenuAdded(MenuItem item);

    /// <summary>
    /// Base menu item class.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public abstract class MenuItem : AimpUIItem
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="MenuItem"/> class.
        /// </summary>
        /// <param name="text">The text.</param>
        protected MenuItem(string text) : base(text)
        {
            _visible = true;
            _enabled = true;
            ChildItems = new MenuItemCollection();
        }

        /// <summary>
        /// Gets or sets the parent menu identifier.
        /// </summary>
        /// <value>
        /// The parent menu identifier.
        /// </value>
        public ParentMenuType ParentMenuId { get; set; }

        /// <summary>
        /// Gets or sets the type of the menu item.
        /// </summary>
        /// <value>
        /// The type of the menu item.
        /// </value>
        public MenuItemType MenuItemType { get; protected set; }
        
        private bool _visible;

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="MenuItem"/> is visible.
        /// </summary>
        /// <value>
        ///   <c>true</c> if visible; otherwise, <c>false</c>.
        /// </value>
        public bool Visible 
        {
            get
            {
                return _visible;
            }
            set
            {
                if (_visible != value)
                {
                    _visible = value;
                    OnPropertyChanged("Visible");
                }
            }
        }

        /// <summary>
        /// Gets or sets the child menu items.
        /// </summary>
        /// <value>
        /// The child items.
        /// </value>
        public MenuItemCollection ChildItems { get; set; }

        private AimpUIItem _actionItem;

        /// <summary>
        /// Gets or sets the associated action item.
        /// </summary>
        public AimpUIItem ActionItem
        {
            get
            {
                return _actionItem;
            }
            set
            {
                if (_actionItem == null || !_actionItem.Equals(value))
                {
                    _actionItem = value;
                    OnPropertyChanged("ActionItem");
                }
            }
        }

        public Bitmap Image { get; set; }

        private bool _enabled;

        public bool Enabled
        {
            get
            {
                return _enabled;
            }
            set
            {
                _enabled = value;
                OnPropertyChanged("Enabled");
            }
        }

        /// <summary>
        /// Occurs when button was clicked.
        /// </summary>
        public event EventHandler Click;

        /// <summary>
        /// Occurs before button will be show.
        /// </summary>
        public event EventHandler BeforeShow;

        public Bitmap Glyph { get; set; }

        public void AddSubItem(MenuItem item)
        {
            ChildItems.Add(this, item);
        }

        public void InsertSubItem(MenuItem item, int index)
        {
            if (index < 0 || index > ChildItems.Count)
            {
                throw new IndexOutOfRangeException();
            }
            
            ChildItems.InsertItem(index, item);
        }

        public IntPtr AimpMenuItemHeader { get; set; }

        /// <summary>
        /// Called when [click].
        /// </summary>
        internal virtual void OnClick()
        {
            var tmp = System.Threading.Interlocked.CompareExchange(ref Click, null, null);
            if (tmp != null)
            {
                tmp(this, EventArgs.Empty);
            }
        }

        internal virtual void OnBeforeShow()
        {
            var tmp = System.Threading.Interlocked.CompareExchange(ref BeforeShow, null, null);
            if (tmp != null)
            {
                tmp(this, EventArgs.Empty);
            }            
        }
    }
}