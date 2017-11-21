using AIMP.SDK;
using AIMP.SDK.MenuManager;

namespace AIMP.DotNet.MusicLibrary
{
    [AimpPlugin("MusicLibraryDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MusicLibrary demo plugin")]
    public class MusicLibraryDemoPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            var demoLibrary = new DemoMusicLibrary(Player);
            var schemaExtension = new DemoExtensionFileSystem();
            var fileINfoProvider = new MyExtensionFileInfoProvider();

            //_smartPlaylistsFactory = new SmartPlaylistsFactory();

            CheckActionResult(Player.Core.RegisterExtension(schemaExtension));
            CheckActionResult(Player.Core.RegisterExtension(fileINfoProvider));
            CheckActionResult(Player.Core.RegisterExtension(demoLibrary));
            //CheckActionResult(Player.Core.RegisterExtension());

            IAimpMenuItem menuItem;
            Player.MenuManager.CreateMenuItem(out menuItem);
            menuItem.Id = "DemoPlugin.CreateSmartPL";
            menuItem.Name = "Create smart Playlist";
            menuItem.OnExecute += (sender, args) =>
            {
            };

            Player.MenuManager.Add(ParentMenuType.AIMP_MENUID_ML_TREE_CONTEXT_FUNCTIONS, menuItem);
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
