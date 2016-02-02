using System.Drawing;

namespace AIMP.SDK.GUI.Controls
{
    public enum AimpImageStretchMode
    {
        Fill,
        Fit,
        Stretch,
        Tile
    }

    public interface IAimpUIImage : IAimpUIControl
    {
        /// <summary>
        /// Gets or sets the image.
        /// </summary>
        Bitmap Image { get; set; }

        /// <summary>
        /// Gets or sets the image stretch mode.
        /// </summary>
        AimpImageStretchMode ImageStretchMode { get; set; }

        /// <summary>
        /// Gets or sets the image list. Use it if Image property not set.
        /// </summary>
        IAimpUIImageList ImageList { get; set; }

        /// <summary>
        /// Gets or sets the index of the image.
        /// </summary>
        int ImageIndex { get; set; }
    }
}