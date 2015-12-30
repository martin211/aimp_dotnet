namespace dotnet_albumart
{
    using System.Drawing;

    using AIMP.SDK;
    using AIMP.SDK.AlbumArtManager;
    using AIMP.SDK.PlayList;

    public class AimpExtensionAlbumArtCatalog : IAimpExtensionAlbumArtCatalog
    {
        #region Implementation of IAimpExtensionAlbumArtCatalog

        public Bitmap GetIcon()
        {
            return Properties.Resources.lastfm;
        }

        public string GetName()
        {
            return "Test catalog";
        }

        public AimpActionResult Show(string fileUrl, string artist, string album, out Bitmap image)
        {
            image = Properties.Resources.front;
            return AimpActionResult.Ok;
        }

        #endregion

        #region Implementation of IAimpExtensionAlbumArtCatalog2

        public AimpActionResult Show(IAimpFileInfo fileInfo, out Bitmap image)
        {
            image = Properties.Resources.front;
            return AimpActionResult.Ok;
        }

        #endregion
    }
}