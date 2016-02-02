using AIMP.SDK.GUI.Controls.Events;

namespace AIMP.SDK.GUI.Controls
{
    // ReSharper disable once InconsistentNaming
    public interface IAimpUISlider : IAimpUIWinControl, IAimpUIChangeEvents, IAimpUIDrawEvents
    {
        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUISlider"/> is horizontal.
        /// </summary>
        /// <value>
        ///   <c>true</c> if horizontal; otherwise, <c>false</c>.
        /// </value>
        bool Horizontal { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUISlider"/> is marks.
        /// </summary>
        /// <value>
        ///   <c>true</c> if marks; otherwise, <c>false</c>.
        /// </value>
        bool Marks { get; set; }

        /// <summary>
        /// Gets or sets the size of the page.
        /// </summary>
        /// <value>
        /// The size of the page.
        /// </value>
        int PageSize { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUISlider"/> is transparent.
        /// </summary>
        /// <value>
        ///   <c>true</c> if transparent; otherwise, <c>false</c>.
        /// </value>
        bool Transparent { get; set; }

        /// <summary>
        /// Gets or sets the value.
        /// </summary>
        /// <value>
        /// The value.
        /// </value>
        int Value { get; set; }

        /// <summary>
        /// Gets or sets the default value.
        /// </summary>
        /// <value>
        /// The default value.
        /// </value>
        int ValueDefault { get; set; }

        /// <summary>
        /// Gets or sets the value maximum.
        /// </summary>
        /// <value>
        /// The value maximum.
        /// </value>
        int ValueMax { get; set; }

        /// <summary>
        /// Gets or sets the value minimum.
        /// </summary>
        /// <value>
        /// The value minimum.
        /// </value>
        int ValueMin { get; set; }
    }
}