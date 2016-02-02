namespace AIMP.SDK.GUI.Controls
{
    public interface IAimpUICategory : IAimpUIWinControl
    {
        /// <summary>
        /// Gets or sets a value indicating whether [automatic size].
        /// </summary>
        bool AutoSize { get; set; }

        /// <summary>
        /// Gets or sets the caption.
        /// </summary>
        string Caption { get; set; }
    }
}