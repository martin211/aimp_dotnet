namespace dotnet_albumart
{
    using System.Drawing;

    using AIMP.SDK;
    using AIMP.SDK.AlbumArtManager;
    using AIMP.SDK.PlayList;

    public class AimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider
    {
        #region Implementation of IAimpExtensionAlbumArtProvider2

        public AimpActionResult Get(IAimpFileInfo fileInfo, object options, Bitmap image)
        {
            throw new System.NotImplementedException();
        }

        #endregion

        #region Implementation of IAimpExtensionAlbumArtProvider

        public AimpActionResult Get(string fileUrl, string artist, string album, object options, Bitmap image)
        {
            throw new System.NotImplementedException();
        }

        #endregion

        #region Implementation of IAimpExtensionAlbumArtProvider

        public AimpAlbumArtProviderCategory GetCategory()
        {
            return AimpAlbumArtProviderCategory.AIMP_ALBUMART_PROVIDER_CATEGORY_INTERNET;
        }

        #endregion
    }
}