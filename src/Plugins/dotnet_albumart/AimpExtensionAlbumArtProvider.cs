// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using AIMP.SDK.FileManager;

namespace dotnet_albumart
{
    using System.Drawing;
    using AIMP.SDK;
    using AIMP.SDK.AlbumArtManager;

    public class AimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider
    {
        #region Implementation of IAimpExtensionAlbumArtProvider2

        public AimpActionResult Get(IAimpFileInfo fileInfo, IAimpAlbumArtSearchOptions options, out Bitmap image)
        {
            image = Properties.Resources.front;
            return AimpActionResult.OK;
        }

        #endregion

        #region Implementation of IAimpExtensionAlbumArtProvider

        public AimpActionResult Get(string fileUrl, string artist, string album, IAimpAlbumArtSearchOptions options, out Bitmap image)
        {
            image = Properties.Resources.front;
            return AimpActionResult.OK;
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