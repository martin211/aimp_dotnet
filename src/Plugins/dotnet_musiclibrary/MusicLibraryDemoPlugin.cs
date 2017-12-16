using AIMP.DotNet.MusicLibrary.Preimage;
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
            var preimageFactory = new MediaLibraryPreimageFactory();
            var plListner = new PlaylistManagerListener();


            CheckActionResult(Player.Core.RegisterExtension(schemaExtension));
            CheckActionResult(Player.Core.RegisterExtension(fileINfoProvider));
            CheckActionResult(Player.Core.RegisterExtension(demoLibrary));

            CheckActionResult(Player.Core.RegisterExtension(plListner));
            CheckActionResult(Player.Core.RegisterExtension(preimageFactory));
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
