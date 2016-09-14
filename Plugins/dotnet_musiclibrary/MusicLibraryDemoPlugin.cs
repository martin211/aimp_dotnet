using AIMP.SDK;

namespace dotnet_musiclibrary
{
    [AimpPlugin("MusicLibraryDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MusicLibrary demo plugin")]
    public class MusicLibraryDemoPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            var demoLibrary = new DemoMusicLibrary();
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
