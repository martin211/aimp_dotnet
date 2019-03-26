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
using AIMP.SDK.FileManager;

namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    /// <summary>
    /// It is the second edition of the <seealso cref="IAimpExtensionAlbumArtProvider"/> interface.
    /// </summary>
    public interface IAimpExtensionAlbumArtProvider2
    {
        /// <summary>
        /// Gets the album art image.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="options">The search options <seealso cref="IAimpAlbumArtSearchOptions"/>.</param>
        /// <param name="image">Out. The album art image.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult Get(IAimpFileInfo fileInfo, IAimpAlbumArtSearchOptions options, out Bitmap image);
    }
}