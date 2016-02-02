namespace AIMP.SDK.GUI.Controls
{
    public enum AimpUICheckboxStateType
    {
        Unchecked = 0,
        Checked,
        Unknown
    }

    public interface IAimpUICheckBox : IAimpUIWinControl
    {
        /// <summary>
        /// Gets or sets a value indicating whether [automatic size].
        /// </summary>
        bool AutoSize { get; set; }

        /// <summary>
        /// Gets or sets the caption.
        /// </summary>
        string Caption { get; set; }

        /// <summary>
        /// Gets or sets the state.
        /// </summary>
        AimpUICheckboxStateType State { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [word wrap].
        /// </summary>
        bool WordWrap { get; set; }
    }
}