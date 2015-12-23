using System;

namespace dotnet_albumart
{
    using AIMP.SDK;
    using AIMP.SDK.AlbumArtManager;

    [AimpPlugin("AlbumArtDemoPlugin", "Evgeniy Bogdan", "1", AimpPluginType = AimpPluginType.Addons, FullDescription = "Album art catalog extension demo")]
    public class AlbumArtDemoPlugin : AimpPlugin
    {
        private IAimpExtensionAlbumArtCatalog _catalog;

        #region Overrides of AimpPlugin

        /// <summary>
        /// Inside this function, plugin should perform all initialization
        /// </summary>
        public override void Initialize()
        {
            _catalog = new AimpExtensionAlbumArtCatalog();
            Player.Core.RegisterExtension(_catalog);
        }

        /// <summary>
        /// Inside this function, plugin should dispose all resources
        /// </summary>
        public override void Dispose()
        {
            Player.Core.UnregisterExtension(_catalog);
        }

        #endregion
    }
}
