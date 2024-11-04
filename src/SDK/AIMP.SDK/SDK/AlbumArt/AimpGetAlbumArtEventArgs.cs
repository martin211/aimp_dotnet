//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

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
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpGetAlbumArtEventArgs"/> class
        /// </summary>
        /// <param name="image">The image</param>
        /// <param name="userData">The user data</param>
        public AimpGetAlbumArtEventArgs(IAimpImage image, object userData = null)
        {
            UserData = userData;
            Image = image;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpGetAlbumArtEventArgs"/> class
        /// </summary>
        /// <param name="image">The image</param>
        /// <param name="imageContainer">The image container</param>
        /// <param name="userData">The user data</param>
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
