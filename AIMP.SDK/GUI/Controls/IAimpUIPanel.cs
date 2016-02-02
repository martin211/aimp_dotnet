namespace AIMP.SDK.GUI.Controls
{
    using AIMP.SDK.GUI.Controls.Events;

    // ReSharper disable once InconsistentNaming
    public interface IAimpUIPanel : IAimpUIWinControl, IAimpUIDrawEvents
    {
        /// <summary>
        /// Gets or sets a value indicating whether [automatic size].
        /// </summary>
        /// <value>
        ///   <c>true</c> if [automatic size]; otherwise, <c>false</c>.
        /// </value>
        bool AutoSize { get; set; }

        /// <summary>
        /// Gets or sets the borders.
        /// </summary>
        /// <value>
        /// The borders.
        /// </value>
        AimpBorders Borders { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIPanel"/> is transparent.
        /// </summary>
        /// <value>
        ///   <c>true</c> if transparent; otherwise, <c>false</c>.
        /// </value>
        bool Transparent { get; set; }

        /// <summary>
        /// Gets or sets the padding.
        /// </summary>
        /// <value>
        /// The padding.
        /// </value>
        int Padding { get; set; }
    }
}