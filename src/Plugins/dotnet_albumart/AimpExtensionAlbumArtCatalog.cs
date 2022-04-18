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

using AIMP.SDK.AlbumArt.Extensions;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;

namespace dotnet_albumart
{
    using System.Drawing;
    using AIMP.SDK;

    public class AimpExtensionAlbumArtCatalog : IAimpExtensionAlbumArtCatalog
    {
        public AimpActionResult<Bitmap> Show(IAimpFileInfo fileInfo)
        {
            var image = Properties.Resources.front;
            return new AimpActionResult<Bitmap>(ActionResultType.OK, image);
        }

        public AimpActionResult<Bitmap> GetIcon()
        {
            return new AimpActionResult<Bitmap>(ActionResultType.OK, Properties.Resources.lastfm);
        }

        public AimpActionResult<string> GetName()
        {
            return new AimpActionResult<string>(ActionResultType.OK, "Test catalog");
        }

        public AimpActionResult<Bitmap> Show(string fileUrl, string artist, string album)
        {
            var image = Properties.Resources.front;
            return new AimpActionResult<Bitmap>(ActionResultType.OK, image);
        }
    }
}
