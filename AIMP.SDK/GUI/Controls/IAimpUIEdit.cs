namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// Aimp one line edit control interface.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIEdit : IAimpUIBaseButtonnedEdit
    {
        /// <summary>
        /// Gets or sets the password character.
        /// </summary>
        char PasswordChar { get; set; }

        /// <summary>
        /// Gets or sets the text hint.
        /// </summary>
        string TextHint { get; set; }

        /// <summary>
        /// Gets or sets the change delay (msec) between changes and raises OnChange event.
        /// </summary>
        int ChangeDelay { get; set; }
    }
}