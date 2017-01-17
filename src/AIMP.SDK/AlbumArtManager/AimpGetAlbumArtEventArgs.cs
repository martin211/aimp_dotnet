namespace AIMP.SDK.AlbumArtManager
{
    using System;
    using System.Drawing;

    /// <summary>
    /// Get album event arguments.
    /// </summary>
    public class AimpGetAlbumArtEventArgs : EventArgs
    {
        /// <summary>
        /// Gets or sets the cover image.
        /// </summary>
        public Bitmap CoverImage { get; set; }
    }
}