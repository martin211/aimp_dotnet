using AIMP.DotNet.MusicLibrary.ExplorerMusicProvider;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.DotNet.MusicLibrary
{
    [AimpPlugin("MusicLibraryDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MusicLibrary demo plugin")]
    public class MusicLibraryDemoPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            var demoLibrary = new DemoMusicLibrary(this.Player);
            if (Player.Core.RegisterExtension(demoLibrary) != AimpActionResult.Ok)
            {
                System.Diagnostics.Debugger.Break();
                System.Diagnostics.Debug.WriteLine("Unable register DemoMusicLibrary");
            }
        }

        public override void Dispose()
        {
            
        }
    }
}
