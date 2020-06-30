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
            var fileINfoProvider = new MyExtensionFileInfoProvider(Player);
            var preimageFactory = new MediaLibraryPreimageFactory();
            var plListner = new PlaylistManagerListener();


            CheckActionResult(Player.Core.RegisterExtension(schemaExtension).ResultType);
            CheckActionResult(Player.Core.RegisterExtension(fileINfoProvider).ResultType);
            CheckActionResult(Player.Core.RegisterExtension(demoLibrary).ResultType);

            CheckActionResult(Player.Core.RegisterExtension(plListner).ResultType);
            CheckActionResult(Player.Core.RegisterExtension(preimageFactory).ResultType);
        }

        public override void Dispose()
        {
            
        }

        private void CheckActionResult(ActionResultType result)
        {
            if (result != ActionResultType.OK)
            {
                System.Diagnostics.Debugger.Break();
            }
        }
    }
}
