using System;
using System.ComponentModel;

namespace AIMP.SDK.UI
{
    /// <summary>
    /// Base Aimp User Interface item.
    /// </summary>
    // ReSharper disable InconsistentNaming
    public abstract class AimpUIItem : MarshalByRefObject
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
            Id = $"aimp_uiitem_{GetHashCode()}";
        }

        /// <summary>
        /// Gets or sets the menu identifier.
        /// </summary>
        /// <value>
        /// The identifier.
        /// </value>
        public string Id { get; set; }

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        /// <value>
        /// The text.
        /// </value>
        public string Text { get; set; }
    }
}