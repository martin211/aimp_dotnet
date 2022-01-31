// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System.Drawing;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.AlbumArt.Extensions
{
    /// <summary>
    /// It is the second edition of the <seealso cref="IAimpExtensionAlbumArtProvider" /> interface.
    /// </summary>
    public interface IAimpExtensionAlbumArtProvider2
    {
        /// <summary>
        /// Gets the album art image.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="options">The search options <seealso cref="IAimpAlbumArtSearchOptions" />.</param>
        /// <returns>AimpActionResult&lt;Bitmap&gt;.</returns>
        AimpActionResult<Bitmap> Get(IAimpFileInfo fileInfo, IAimpAlbumArtSearchOptions options);
    }
}
