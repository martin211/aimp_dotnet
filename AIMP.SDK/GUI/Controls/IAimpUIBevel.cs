namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// Вesigned to draw frame around the some object or separate two objects groups via simple line.
    /// </summary>
    public interface IAimpUIBevel : IAimpUIControl
    {
        /// <summary>
        /// Gets or sets the borders.
        /// </summary>
        /// <value>
        /// The borders.
        /// </value>
        AimpBorders Borders { get; set; }
    }
}