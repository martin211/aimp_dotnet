using System;
using System.Drawing;

namespace AIMP.SDK.Services.AlbumArtManager
{
    /// <summary>
    /// Get album event arguments.
    /// </summary>
    public class GetAlbumArtEventArgs : EventArgs
    {
        /// <summary>
        /// Gets or sets the cover image.
        /// </summary>
        public Bitmap CoverImage { get; set; }
    }
}