//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Drawing;

namespace AIMP.SDK.AlbumArt
{
    /// <summary>
    /// Get album event arguments.
    /// Implements the <see cref="System.EventArgs" />
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class AimpGetAlbumArtEventArgs : EventArgs
    {
        /// <summary>
        /// Gets or sets the cover image.
        /// </summary>
        /// <value>The cover image.</value>
        public Bitmap CoverImage { get; set; }
    }
}
