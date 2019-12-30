// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK.Objects;

namespace AIMP.SDK.AlbumArtManager
{
    using System;

    /// <summary>
    /// Get album event arguments.
    /// </summary>
    public class AimpGetAlbumArtEventArgs : EventArgs
    {
        /// <summary>
        /// Gets or sets the cover image.
        /// </summary>
        public IAimpImage CoverImage { get; set; }
    }
}