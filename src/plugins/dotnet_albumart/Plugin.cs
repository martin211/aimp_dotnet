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

using AIMP;
using AIMP.SDK.AlbumArt.Extensions;

namespace dotnet_albumart
{
    [AimpPlugin("AlbumArtDemoPlugin", "Evgeniy Bogdan", "1.0.0.0", AimpPluginType = AimpPluginType.Addons,
        FullDescription = "Album art catalog extension demo")]
    public class Plugin : AimpPlugin
    {
        private IAimpExtensionAlbumArtCatalog _catalog;

        private IAimpExtensionAlbumArtProvider _provider;

        #region Overrides of AimpPlugin

        /// <summary>
        /// Inside this function, plugin should perform all initialization
        /// </summary>
        public override void Initialize()
        {
            _catalog = new AimpExtensionAlbumArtCatalog();
            _provider = new AimpExtensionAlbumArtProvider();
            Player.Core.RegisterExtension(_catalog);
            Player.Core.RegisterExtension(_provider);
        }

        /// <summary>
        /// Inside this function, plugin should dispose all resources
        /// </summary>
        public override void Dispose()
        {
            Player.Core.UnregisterExtension(_catalog);
            Player.Core.UnregisterExtension(_provider);
        }

        #endregion
    }
}
