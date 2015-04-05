namespace AIMP.SDK.UI.ActionItem
{
    /// <summary>
    /// Action item.
    /// </summary>
    public class AimpActionItem : AimpUIItem
    {
        private object _customData;

        private string _groupName;

        private bool _enabled;

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpActionItem" /> class.
        /// </summary>
        /// <param name="text">The item text.</param>
        /// <param name="groupName">Name of the group.</param>
        public AimpActionItem(string text, string groupName) : base(text)
        {
            GroupName = groupName;
            Enabled = true;
        }

        /// <summary>
        /// Gets or sets the some custom data.
        /// </summary>
        /// <value>
        /// The data.
        /// </value>
        public object Data
        {
            get
            {
                return _customData;
                
            }
            set
            {
                if (_customData == null || _customData != value)
                {
                    _customData = value;
                    OnPropertyChanged("Data");
                }
            }
        }

        /// <summary>
        /// Gets or sets the name of the group.
        /// </summary>
        /// <value>
        /// The name of the group.
        /// </value>
        public string GroupName
        {
            get
            {
                return _groupName;
            }
            set
            {
                if (string.IsNullOrWhiteSpace(_groupName) || !_groupName.Equals(value))
                {
                    _groupName = value;
                    OnPropertyChanged("GroupName");
                }
            }
        }

        /// <summary>
        /// Gets or sets the global hot key.
        /// </summary>
        /// <value>
        /// The global hot key.
        /// </value>
        public int GlobalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the second global hot key.
        /// </summary>
        /// <value>
        /// The global hot key2.
        /// </value>
        public int GlobalHotKey2 { get; set; }

        /// <summary>
        /// Gets or sets the local hot key.
        /// </summary>
        /// <value>
        /// The local hot key.
        /// </value>
        public int LocalHotKey { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="AimpActionItem"/> is enabled.
        /// </summary>
        /// <value>
        ///   <c>true</c> if enabled; otherwise, <c>false</c>.
        /// </value>
        public bool Enabled
        {
            get
            {
                return _enabled;

            }
            set
            {
                if (_enabled != value)
                {
                    _enabled = value;
                    OnPropertyChanged("Enabled");
                }
            }
        }
    }
}