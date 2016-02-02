namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// Aimp combo box control interface.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIComboBox : IAimpUIBaseComboBox
    {
        /// <summary>
        /// Gets or sets a value indicating whether [automatic complete].
        /// </summary>
        bool AutoComplete { get; set; }

        /// <summary>
        /// Gets or sets the index of the item.
        /// </summary>
        int ItemIndex { get; set; }

        /// <summary>
        /// Gets or sets the item object.
        /// </summary>
        object ItemObject { get; set; }

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        new string Text { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [read only].
        /// </summary>
        new bool ReadOnly { get; set; }
    }
}