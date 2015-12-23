namespace AIMP.SDK.AlbumArtManager
{
    using System.Drawing;

    using AIMP.SDK.PlayList;

    public interface IAimpExtensionAlbumArtProvider2
    {
        AimpActionResult Get(IAimpFileInfo fileInfo, object options, Bitmap image);
    }
}