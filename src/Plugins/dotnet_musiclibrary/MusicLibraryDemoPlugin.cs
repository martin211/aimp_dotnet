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
        private SmartPlaylistsFactory _smartPlaylistsFactory;

        public override void Initialize()
        {
            var demoLibrary = new DemoMusicLibrary(Player);
            var schemaExtension = new DemoExtensionFileSystem();
            var fileINfoProvider = new MyExtensionFileInfoProvider();
            var listner = new FrmTestPreimage(Player.PlaylistManager, Player.Core);

            //_smartPlaylistsFactory = new SmartPlaylistsFactory();

            CheckActionResult(Player.Core.RegisterExtension(schemaExtension));
            CheckActionResult(Player.Core.RegisterExtension(fileINfoProvider));
            CheckActionResult(Player.Core.RegisterExtension(demoLibrary));
            CheckActionResult(Player.Core.RegisterExtension(_smartPlaylistsFactory));
            //CheckActionResult(Player.Core.RegisterExtension());

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
