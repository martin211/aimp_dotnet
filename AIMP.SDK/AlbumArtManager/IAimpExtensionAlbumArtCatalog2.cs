namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    using AIMP.SDK.PlayList;

    public interface IAimpExtensionAlbumArtCatalog2
    {
        AimpActionResult Show(IAimpFileInfo fileInfo, out Bitmap image);
    }
}