namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    public enum AimpAlbumArtProviderCategory
    {
        AIMP_ALBUMART_PROVIDER_CATEGORY_TAGS,

        AIMP_ALBUMART_PROVIDER_CATEGORY_FILE,

        AIMP_ALBUMART_PROVIDER_CATEGORY_INTERNET
    }

    public interface IAimpExtensionAlbumArtProvider
    {
        AimpActionResult Get(string fileUrl, string artist, string album, object options, Bitmap image);

        AimpAlbumArtProviderCategory GetCategory();
    }
}