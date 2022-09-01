//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Drawing.Imaging;
using System.IO;
using AIMP.SDK.AlbumArt;
using AIMP.SDK.AlbumArt.Extensions;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

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
            return AimpAlbumArtProviderCategory.Internet;
        }
    }

    internal class AimpExtensionAlbumArtProvider3 : IAimpExtensionAlbumArtProvider3
    {
        private readonly IAimpCore _core;

        public AimpExtensionAlbumArtProvider3(IAimpCore core)
        {
            _core = core;
        }

        public AimpActionResult<IAimpImageContainer> Get(IAimpFileInfo file, IAimpAlbumArtRequest requestOption)
        {
            var containerResult = _core.CreateAimpObject<IAimpImageContainer>();
            var container = containerResult.Result;

            var image = Properties.Resources.front;
            using (var stream = new MemoryStream())
            {
                image.Save(stream, ImageFormat.Jpeg);
                container.SetDataSize(stream.Length);
                var containerData = container.GetData();
                stream.Read(containerData.Result, 0, (int)stream.Length);
            }

            return new AimpActionResult<IAimpImageContainer>(ActionResultType.OK, container);
        }

        public AimpAlbumArtProviderCategory GetCategory()
        {
            return AimpAlbumArtProviderCategory.Internet;
        }
    }
}
