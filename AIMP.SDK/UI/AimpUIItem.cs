using System;
using System.ComponentModel;

namespace AIMP.SDK.UI
{
    /// <summary>
    /// Base Aimp User Interface item.
    /// </summary>
    // ReSharper disable InconsistentNaming
    public abstract class AimpUIItem : MarshalByRefObject, INotifyPropertyChanged
    // ReSharper restore InconsistentNaming
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpUIItem"/> class.
        /// </summary>
        /// <param name="text">The item text.</param>
        protected AimpUIItem(string text) : this()
        {
            Text = text;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpUIItem"/> class.
        /// </summary>
        protected AimpUIItem()
        {
            // ReSharper disable DoNotCallOverridableMethodsInConstructor
            Id = string.Format("AIMP.UIItem.{0}", GetHashCode());
            // ReSharper restore DoNotCallOverridableMethodsInConstructor
        }

        private string _id;
        /// <summary>
        /// Gets or sets the menu identifier.
        /// </summary>
        /// <value>
        /// The identifier.
        /// </value>
        public string Id
        {
            get
            {
                return _id;
            }
            set
            {
                if (string.IsNullOrEmpty(_id) || !_id.Equals(value))
                {
                    _id = value;
                    OnPropertyChanged("Id");
                }
            }
        }

        private string _text;
        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        /// <value>
        /// The text.
        /// </value>
        public string Text
        {
            get
            {
                return _text;
            }
            set
            {
                if (string.IsNullOrEmpty(_text) || !_text.Equals(value))
                {
                    _text = value;
                    OnPropertyChanged("Text");
                }
            }
        }

        /// <summary>
        /// Occurs when a property value changes.
        /// </summary>
        public event PropertyChangedEventHandler PropertyChanged;

        /// <summary>
        /// Called when [property changed].
        /// </summary>
        /// <param name="propertyName">Name of the property.</param>
        //[NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged(string propertyName)
        {
            var handler = PropertyChanged;
            handler?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }
    }
}