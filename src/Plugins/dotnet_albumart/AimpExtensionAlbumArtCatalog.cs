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
            return new AimpActionResult<string>(ActionResultType.OK,"Test catalog");
        }

        public AimpActionResult<Bitmap> Show(string fileUrl, string artist, string album)
        {
            var image = Properties.Resources.front;
            return new AimpActionResult<Bitmap>(ActionResultType.OK, image);
        }
    }
}