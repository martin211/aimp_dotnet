namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    using AIMP.SDK.PlayList;

    public enum AimpAlbumArtProviderCategory
    {
        AIMP_ALBUMART_PROVIDER_CATEGORY_TAGS,

        AIMP_ALBUMART_PROVIDER_CATEGORY_FILE,

        AIMP_ALBUMART_PROVIDER_CATEGORY_INTERNET
    }

    public interface IAimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider2, IAimpExtension
    {
        AimpActionResult Get(string fileUrl, string artist, string album, IAimpAlbumArtSearchOptions options, out Bitmap image);

        AimpAlbumArtProviderCategory GetCategory();
    }
}