using AIMP.SDK.GUI.Controls.Form;

namespace AIMP.SDK.GUI.Controls
{
    public enum AimpCheckModeType
    {
        Hide = 0,
        Visible,
        // TODO: rename
        StateChange
    }

    public interface IAimpUIGroupBox : IAimpUIWinControl
    {
        /// <summary>
        /// Gets or sets a value indicating whether [automatic size].
        /// </summary>
        bool AutoSize { get; set; }

        /// <summary>
        /// Gets or sets the border style.
        /// </summary>
        AimpBorderStyle BorderStyle { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIGroupBox" /> is traasparent.
        /// </summary>
        bool Transparent { get; set; }

        /// <summary>
        /// Gets or sets the check mode.
        /// </summary>
        AimpCheckModeType CheckMode { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIGroupBox"/> is chaecked.
        /// </summary>
        bool Chaecked { get; set; }
    }
}