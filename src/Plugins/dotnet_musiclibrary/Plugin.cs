//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

using AIMP.DotNet.MusicLibrary.Preimage;
using AIMP.SDK;
using AIMP.SDK.MenuManager;
using AIMP.SDK.MenuManager.Objects;
using AIMP.SDK.MusicLibrary;

namespace AIMP.DotNet.MusicLibrary
{
    [AimpPlugin("MusicLibraryDemoPlugin", "Martin", "1.0.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "MusicLibrary demo plugin")]
    public class Plugin : AimpPlugin
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

            var menu = Player.Core.CreateAimpObject<IAimpMenuItem>();
            menu.Result.Name = "Test";

            menu.Result.OnShow += (sender, args) =>
            {
                var storage = Player.ServiceMusicLibrary.GetActiveStorage();
                var name = storage.Result.Caption;
                var p = storage.Result.GroupingPreset;
                var id = storage.Result.Id;

                var focusedFiles = Player.ServiceMusicLibraryUi.GetFiles(FilesType.Focused);
            };

            Player.ServiceMenuManager.Add(ParentMenuType.MlTreeContextFunctions, menu.Result);

            var tableMenu = Player.Core.CreateAimpObject<IAimpMenuItem>();
            menu.Result.Name = "Library Demo plugin";
            menu.Result.Id = Guid.NewGuid().ToString();
            menu.Result.OnExecute += (sender, args) =>
            {
                var focusedFiles = Player.ServiceMusicLibraryUi.GetFiles(FilesType.Focused);
            };
            Player.ServiceMenuManager.Add(ParentMenuType.MlTableContextFunctions, tableMenu.Result);
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
