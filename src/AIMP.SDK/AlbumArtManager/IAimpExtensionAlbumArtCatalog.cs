﻿namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;
    //TODO ADN-25
    /// <summary>
    /// This interface is a extension for the IAimpServiceAlbumArt service. 
    /// It allows for the plugin to add a menu item to the context menu for external album art catalogs.
    /// </summary>
    /// <seealso cref="AIMP.SDK.AlbumArtManager.IAimpExtensionAlbumArtCatalog2" />
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
    public interface IAimpExtensionAlbumArtCatalog : IAimpExtensionAlbumArtCatalog2, IAimpExtension
    {
        /// <summary>
        /// Gets icon for menu item, icon must be 16x16.
        /// </summary>
        Bitmap GetIcon();

        /// <summary>
        /// Gets the catalog name.
        /// </summary>
        string GetName();

        /// <summary>
        /// This method will be called on menu item click.
        /// </summary>
        /// <param name="fileUrl">The file URL.</param>
        /// <param name="artist">Optional. The artist. , can be null</param>
        /// <param name="album">Optional. The album.</param>
        /// <param name="image">Image instance, can be null if catalog does not provides an ability to select album art immediately.
        /// For example, if the extension just open external link via Internet browser.</param>
        /// <returns>The <see cref="AimpActionResult"/> result.</returns>
        AimpActionResult Show(string fileUrl, string artist, string album, out Bitmap image);
    }
}