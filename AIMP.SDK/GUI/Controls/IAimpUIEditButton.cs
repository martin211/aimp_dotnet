namespace AIMP.SDK.GUI.Controls
{
    using Events;

    /// <summary>
    /// Button control inside edit control.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIEditButton : IAimpUIChangeEvents
    {
        /// <summary>
        /// Gets or sets the custom data.
        /// </summary>
        string Custom { get; set; }

        /// <summary>
        /// Gets or sets the caption.
        /// </summary>
        string Caption { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIEditButton"/> is enabled.
        /// </summary>
        bool Enabled { get; set; }

        /// <summary>
        /// Gets or sets the hint.
        /// </summary>
        string Hint { get; set; }

        /// <summary>
        /// Gets or sets the index.
        /// </summary>
        int Index { get; set; }

        /// <summary>
        /// Gets or sets the index of the image.
        /// </summary>
        int ImageIndex { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIEditButton"/> is visible.
        /// </summary>
        bool Visible { get; set; }

        /// <summary>
        /// Gets or sets the width.
        /// </summary>
        string Width { get; set; }
    }
}