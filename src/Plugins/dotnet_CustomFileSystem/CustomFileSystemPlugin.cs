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

using System;
using System.IO;
using System.Linq;
using AIMP.SDK.MenuManager;

namespace AIMP.SDK.CustomFileSystem
{
    [AimpPlugin("dotnet_CustomFileSystem", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons,
        RequireAppDomain = false)]
    [Serializable]
    // ReSharper disable UnusedMember.Global
    public class CustomFileSystemPlugin : AimpPlugin
        // ReSharper restore UnusedMember.Global
    {
        public override void Initialize()
        {
            var getResult = Player.ServiceMenuManager.GetBuiltIn(ParentMenuType.PlayerPlaylistAdding);
            var item = Player.Core.CreateAimpObject<IAimpMenuItem>().Result;
            item.Name = "MyMusic: Add All Files";
            item.Parent = getResult.Result;
            item.OnExecute += Item_OnExecute;
            Player.ServiceMenuManager.Add(item);

            CustomFileSystem fileSystem = new CustomFileSystem(Player);
            //ExtensionFileInfo fileInfo = new ExtensionFileInfo();

            // Register custom file system
            Player.Core.RegisterExtension(fileSystem);
        }

        private void Item_OnExecute(object sender, System.EventArgs e)
        {
            var dir = Environment.GetFolderPath(Environment.SpecialFolder.MyMusic);
            var files = Directory.GetFiles(dir, "*.mp3");

            var filesToPlaylist = files
                .Where(file => Player.ServiceFileFormats.IsSupported(file, FileManager.FileFormats.Audio).ResultType ==
                               ActionResultType.OK)
                .Select(f => $"{CustomFileSystem.MySchemePrefix}{f}").ToList();
            if (filesToPlaylist.Any())
            {
                var r = Player.ServicePlaylistManager.GetActivePlaylist();
                if (r.ResultType == ActionResultType.OK)
                {
                    r.Result.AddList(filesToPlaylist, Playlist.PlaylistFlags.NoCheckFormat,
                        Playlist.PlaylistFilePosition.EndPosition);
                }
            }
        }

        public override void Dispose()
        {
        }
    }
}
