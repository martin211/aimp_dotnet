// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
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
    [AimpPlugin("dotnet_CustomFileSystem", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons, RequireAppDomain = false)]
    [Serializable]
    // ReSharper disable UnusedMember.Global
    public class CustomFileSystemPlugin : AimpPlugin
    // ReSharper restore UnusedMember.Global
    {
        public override void Initialize()
        {
            Player.MenuManager.GetBuiltIn(ParentMenuType.AIMP_MENUID_PLAYER_PLAYLIST_ADDING, out var parent);
            Player.MenuManager.CreateMenuItem(out var item);
            item.Name = "MyMusic: Add All Files";
            item.Parent = parent;
            item.OnExecute += Item_OnExecute;
            Player.MenuManager.Add(item);

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
                .Where(file => Player.ServiceFileFormats.IsSupported(file, FileManager.FileFormats.AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO) == AimpActionResult.OK)
                .Select(f => $"{CustomFileSystem.MySchemePrefix}{f}").ToList();
            if (filesToPlaylist.Any())
            {
                if (Player.PlaylistManager.GetActivePlaylist(out var activePl) == AimpActionResult.OK)
                {
                    activePl.AddList(filesToPlaylist, Playlist.PlaylistFlags.NOCHECKFORMAT, Playlist.PlaylistFilePosition.EndPosition);
                }
            }
        }

        public override void Dispose()
        {
            
        }
    }
}
