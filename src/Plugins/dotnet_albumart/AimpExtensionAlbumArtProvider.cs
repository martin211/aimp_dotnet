// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK.AlbumArt;
using AIMP.SDK.AlbumArt.Extensions;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;

namespace dotnet_albumart
{
    using System.Drawing;
    using AIMP.SDK;

    public class AimpExtensionAlbumArtProvider : IAimpExtensionAlbumArtProvider
    {
        public AimpActionResult<Bitmap> Get(IAimpFileInfo fileInfo, IAimpAlbumArtSearchOptions options)
        {
            var image = Properties.Resources.front;
            return new AimpActionResult<Bitmap>(ActionResultType.OK, image);
        }

        public AimpActionResult<Bitmap> Get(string fileUrl, string artist, string album,
            IAimpAlbumArtSearchOptions options)
        {
            var image = Properties.Resources.front;
            return new AimpActionResult<Bitmap>(ActionResultType.OK, image);
        }

        public AimpAlbumArtProviderCategory GetCategory()
        {
            return AimpAlbumArtProviderCategory.AIMP_ALBUMART_PROVIDER_CATEGORY_INTERNET;
        }
    }
}
