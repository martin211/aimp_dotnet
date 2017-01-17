using System;
using AIMP.SDK.ActionManager;

namespace AIMP.SDK.UI.ActionItem
{
    /// <summary>
    /// Action item.
    /// </summary>
    public class AimpActionItem : AimpUIItem, IAimpAction
    {
        private string _customData;

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
        public string CustomData
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
                }
            }
        }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// Gets or sets the name of the group.
        /// </summary>
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
                }
            }
        }

        private int _defaultLocalHotKey;

        /// <summary>
        /// Gets or sets the default hot key.
        /// </summary>
        public int DefaultLocalHotKey
        {
            get
            {
                return _defaultLocalHotKey;
            }
            set
            {
                _defaultLocalHotKey = value;
            }
        }

        private int _defaultGlobalHotKey;

        /// <summary>
        /// Gets or sets the default global hot key.
        /// </summary>
        public int DefaultGlobalHotKey
        {
            get { return _defaultGlobalHotKey; }
            set
            {
                _defaultGlobalHotKey = value;
            }
        }

        private int _defaultGlobalHotKey2;

        /// <summary>
        /// Gets or sets the default global hot key2.
        /// </summary>
        public int DefaultGlobalHotKey2
        {
            get { return _defaultGlobalHotKey2; }
            set
            {
                _defaultGlobalHotKey2 = value;
            }
        }

        public event EventHandler OnExecute;

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
                }
            }
        }
    }
}