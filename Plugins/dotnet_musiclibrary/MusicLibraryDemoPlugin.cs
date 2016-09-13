using AIMP.SDK;

namespace dotnet_musiclibrary
{
    [AimpPlugin("MusicLibraryDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MusicLibrary demo plugin")]
    public class MusicLibraryDemoPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            var demoPlugin = new DemoMusicLibrary();
            if (Player.Core.RegisterExtension(demoPlugin) != AimpActionResult.Ok)
            {
                System.Diagnostics.Debugger.Break();
                System.Diagnostics.Debug.WriteLine("Unable register DemoMusicLibrary");
            }

            var demoGroupingProvider = new CustomAimpGroupingTreeDataProvider();
            if (Player.Core.RegisterExtension(demoGroupingProvider) != AimpActionResult.Ok)
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
