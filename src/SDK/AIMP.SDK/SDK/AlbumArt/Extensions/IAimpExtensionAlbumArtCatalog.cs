using System;
using System.Drawing;

namespace AIMP.SDK.AlbumArt.Extensions;

//TODO ADN-25
/// <summary>
/// This interface is a extension for the IAimpServiceAlbumArt service.
/// It allows for the plugin to add a menu item to the context menu for external album art catalogs.
/// </summary>
/// <seealso cref="IAimpExtensionAlbumArtCatalog2" />
/// <seealso cref="AIMP.SDK.IAimpExtension" />
[Obsolete("Deprecated in AIMP 6.0; use IAimpExtensionAlbumArtProvider3 or IAimpExtensionExternalCatalog.")]
public interface IAimpExtensionAlbumArtCatalog : IAimpExtensionAlbumArtCatalog2, IAimpExtension
{
    /// <summary>
    /// Gets icon for menu item, icon must be 16x16.
    /// </summary>
    /// <returns>AimpActionResult&lt;Bitmap&gt;.</returns>
    AimpActionResult<Bitmap> GetIcon();

    /// <summary>
    /// Gets the catalog name.
    /// </summary>
    /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
    AimpActionResult<string> GetName();

    /// <summary>
    /// This method will be called on menu item click.
    /// </summary>
    /// <param name="fileUrl">The file URL.</param>
    /// <param name="artist">Optional. The artist. , can be null</param>
    /// <param name="album">Optional. The album.</param>
    /// <returns>AimpActionResult&lt;Bitmap&gt;.</returns>
    AimpActionResult<Bitmap> Show(string fileUrl, string artist, string album);
}