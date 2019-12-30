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
using AIMP.SDK.Objects;

namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    /// <summary>
    /// It is the second edition of the <see cref="IAimpExtensionAlbumArtCatalog"/> interface.
    /// </summary>
    public interface IAimpExtensionAlbumArtCatalog2
    {
        /// <summary>
        /// This method will be called on menu item click.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <param name="image">Image instance, can be null if catalog does not provides an ability to select album art immediately.
        /// For example, if the extension just open external link via Internet browser.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult Show(IAimpFileInfo fileInfo, out IAimpImage image);
    }
}