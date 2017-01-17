namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    using AIMP.SDK.PlayList;

    public interface IAimpExtensionAlbumArtCatalog : IAimpExtensionAlbumArtCatalog2, IAimpExtension
    {
        /// <summary>
        /// Gets the catalog icon.
        /// </summary>
        Bitmap GetIcon();

        /// <summary>
        /// Gets the catalog name.
        /// </summary>
        string GetName();

        AimpActionResult Show(string fileUrl, string artist, string album, out Bitmap image);
    }
}