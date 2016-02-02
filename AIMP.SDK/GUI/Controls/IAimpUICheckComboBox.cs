namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// Check box control interface.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUICheckComboBox : IAimpUIBaseComboBox
    {
        /// <summary>
        /// Gets or sets the selected items. Separated by ';'
        /// </summary>
        string SelectedItems { get; set; }

        //AimpActionResult Add(string value, string extraData);

        /// <summary>
        /// Gets the checked.
        /// </summary>
        /// <param name="index">The index.</param>
        long GetChecked(int index);

        /// <summary>
        /// Sets the checked.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="value">if set to <c>true</c> [value].</param>
        AimpActionResult SetChecked(int index, bool value);
    }
}