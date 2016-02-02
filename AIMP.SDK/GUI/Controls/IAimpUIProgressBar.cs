namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// 
    /// </summary>
    public interface IAimpUIProgressBar : IAimpUIControl
    {
        /// <summary>
        /// Gets or sets the maximum.
        /// </summary>
        /// <value>
        /// The maximum.
        /// </value>
        int Max { get; set; }

        /// <summary>
        /// Gets or sets the minimum.
        /// </summary>
        /// <value>
        /// The minimum.
        /// </value>
        int Min { get; set; }

        /// <summary>
        /// Gets or sets the progress.
        /// </summary>
        /// <value>
        /// The progress.
        /// </value>
        int Progress { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIProgressBar"/> is indeterminate.
        /// </summary>
        /// <value>
        ///   <c>true</c> if indeterminate; otherwise, <c>false</c>.
        /// </value>
        bool Indeterminate { get; set; }
    }
}