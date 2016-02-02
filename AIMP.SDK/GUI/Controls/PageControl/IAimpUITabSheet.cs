namespace AIMP.SDK.GUI.Controls.PageControl
{
    /// <summary>
    /// 
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUITabSheet : IAimpUIWinControl
    {
        /// <summary>
        /// Gets or sets the caption.
        /// </summary>
        string Caption { get; set; }

        /// <summary>
        /// Gets or sets the index.
        /// </summary>
        int Index { get; set; }

        ///// <summary>
        ///// Gets or sets a value indicating whether this <see cref="IAimpUITabSheet"/> is visible.
        ///// </summary>
        //new bool Visible { get; set; }
    }
}