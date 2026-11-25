using System;
using System.Drawing;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.AlbumArt.Extensions;

/// <summary>
/// It is the second edition of the <see cref="IAimpExtensionAlbumArtCatalog" /> interface.
/// </summary>
[Obsolete("Deprecated in AIMP 6.0; use IAimpExtensionAlbumArtProvider3 or IAimpExtensionExternalCatalog.")]
public interface IAimpExtensionAlbumArtCatalog2
{
    /// <summary>
    /// This method will be called on menu item click.
    /// </summary>
    /// <param name="fileInfo">The file information.</param>
    /// <returns>AimpActionResult&lt;Bitmap&gt;.</returns>
    AimpActionResult<Bitmap> Show(IAimpFileInfo fileInfo);
}