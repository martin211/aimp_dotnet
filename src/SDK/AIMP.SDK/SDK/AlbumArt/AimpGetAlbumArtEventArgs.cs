//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Drawing;

using AIMP.SDK.Objects;

namespace AIMP.SDK.AlbumArt
{
    /// <summary>
    /// Get album event arguments.
    /// Implements the <see cref="System.EventArgs" />
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class AimpGetAlbumArtEventArgs : EventArgs
    {
        public AimpGetAlbumArtEventArgs(IAimpImage image, object userData = null)
        {
            UserData = userData;
            Image = image;
        }

        public AimpGetAlbumArtEventArgs(IAimpImage image, IAimpImageContainer imageContainer, object userData = null)
        {
            UserData = userData;
            Image = image;
            ImageContainer = imageContainer;
        }

        /// <summary>
        /// Gets or sets the user data.
        /// </summary>
        public object UserData { get; }

        /// <summary>
        /// Gets or sets the image.
        /// </summary>
        public IAimpImage Image { get; }

        /// <summary>
        /// Gets or sets the image container.
        /// </summary>
        public IAimpImageContainer ImageContainer { get; }
    }
}
