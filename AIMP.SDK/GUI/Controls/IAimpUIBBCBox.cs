namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// Allow format text with BB codes
    /// <para>
    /// Allowed BB codes: B, I, U, S, COLOR, URL.
    /// </para>
    /// </summary>
    public interface IAimpUIBBCBox : IAimpUIWinControl
    {
        /// <summary>
        /// Gets or sets the borders.
        /// </summary>
        AimpBorders Borders { get; set; }

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        string Text { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIBBCBox"/> is transparent.
        /// </summary>
        bool Transparent { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [word wrap].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [word wrap]; otherwise, <c>false</c>.
        /// </value>
        bool WordWrap { get; set; }
    }
}