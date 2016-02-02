namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// 
    /// </summary>
    public interface IAimpUITabSheet
    {
        /// <summary>
        /// Gets or sets the caption.
        /// </summary>
        /// <value>
        /// The caption.
        /// </value>
        string Caption { get; set; }

        /// <summary>
        /// Gets or sets the index.
        /// </summary>
        /// <value>
        /// The index.
        /// </value>
        int Index { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUITabSheet"/> is visible.
        /// </summary>
        /// <value>
        ///   <c>true</c> if visible; otherwise, <c>false</c>.
        /// </value>
        bool Visible { get; set; }
    }
}