using System;
using AIMP.DotNet.MusicLibrary.SmartPlaylist;
using AIMP.SDK;
using AIMP.SDK.MenuManager;
using AIMP.SDK.Playlist;

namespace AIMP.DotNet.MusicLibrary
{
    [AimpPlugin("MusicLibraryDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MusicLibrary demo plugin")]
    public class MusicLibraryDemoPlugin : AimpPlugin
    {
        private DemoSmartPlaylistsFactory _demoSmartPlaylistsFactory;

        public override void Initialize()
        {
            var demoLibrary = new DemoMusicLibrary(Player);
            var schemaExtension = new DemoExtensionFileSystem();
            var fileINfoProvider = new MyExtensionFileInfoProvider();
            _demoSmartPlaylistsFactory = new DemoSmartPlaylistsFactory();

            CheckActionResult(Player.Core.RegisterExtension(schemaExtension));
            CheckActionResult(Player.Core.RegisterExtension(fileINfoProvider));
            CheckActionResult(Player.Core.RegisterExtension(demoLibrary));
            CheckActionResult(Player.Core.RegisterExtension(_demoSmartPlaylistsFactory));

            IAimpMenuItem menuItem;
            Player.MenuManager.CreateMenuItem(out menuItem);
            menuItem.Id = "DemoPlugin.CreateSmartPL";
            menuItem.Name = "Create smart Playlist";
            menuItem.OnExecute += MenuItemOnOnExecute;
            Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_ML_TREE_CONTEXT_FUNCTIONS, menuItem);
        }

        private void MenuItemOnOnExecute(object sender, EventArgs eventArgs)
        {
            IAimpPlaylist smartPlaylist;
            Player.PlaylistManager.CreatePlaylist("Test smart", true, out smartPlaylist);
            //smartPlaylist.AimpObjectError += (o, args) =>
            //{
            //    System.Diagnostics.Debugger.Break();
            //};
            smartPlaylist.PreImage = new DemoSmartPlaylist();
            var res = smartPlaylist.ReloadFromPreimage();
            var r = smartPlaylist.PreImage.HasDialog;
        }

        public override void Dispose()
        {
            
        }

        private void CheckActionResult(AimpActionResult result)
        {
            if (result != AimpActionResult.Ok)
            {
                System.Diagnostics.Debugger.Break();
            }
        }
    }
}
