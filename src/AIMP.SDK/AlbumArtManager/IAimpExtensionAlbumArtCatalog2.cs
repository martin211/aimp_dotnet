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

using AIMP.SDK.FileManager;

namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    /// <summary>
    /// It is the second edition of the <see cref="IAimpExtensionAlbumArtCatalog" /> interface.
    /// </summary>
    public interface IAimpExtensionAlbumArtCatalog2
    {
        /// <summary>
        /// This method will be called on menu item click.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <returns>AimpActionResult&lt;Bitmap&gt;.</returns>
        AimpActionResult<Bitmap> Show(IAimpFileInfo fileInfo);
    }
}