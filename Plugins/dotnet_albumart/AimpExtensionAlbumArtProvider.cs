namespace dotnet_albumart
{
    using System.Drawing;
    using System.Runtime.InteropServices.WindowsRuntime;

    using AIMP.SDK;
    using AIMP.SDK.AlbumArtManager;
    using AIMP.SDK.PlayList;

    public class AimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider
    {
        #region Implementation of IAimpExtensionAlbumArtProvider2

        public AimpActionResult Get(IAimpFileInfo fileInfo, IAimpAlbumArtSearchOptions options, out Bitmap image)
        {
            image = Properties.Resources.front;
            return AimpActionResult.Ok;
        }

        #endregion

        #region Implementation of IAimpExtensionAlbumArtProvider

        public AimpActionResult Get(string fileUrl, string artist, string album, IAimpAlbumArtSearchOptions options, out Bitmap image)
        {
            image = Properties.Resources.front;
            return AimpActionResult.Ok;
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