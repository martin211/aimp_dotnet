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
        #region Implementation of IAimpExtensionAlbumArtCatalog2

        public ActionResultType Show(IAimpFileInfo fileInfo, out Bitmap image)
        {
            image = Properties.Resources.front;
            return ActionResultType.OK;
        }

        #endregion

        #region Implementation of IAimpExtensionAlbumArtCatalog

        public Bitmap GetIcon()
        {
            return Properties.Resources.lastfm;
        }

        public string GetName()
        {
            return "Test catalog";
        }

        public ActionResultType Show(string fileUrl, string artist, string album, out Bitmap image)
        {
            image = Properties.Resources.front;
            return ActionResultType.OK;
        }

        #endregion
    }
}