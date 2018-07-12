﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using AIMP.SDK.MenuManager;
using AIMP.SDK.Objects;

namespace AIMP.SDK.CustomFileSystem
{
    [AimpPlugin("dotnet_CustomFileSystem", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons, RequireAppDomain = false)]
    [Serializable]
    public class CustomFileSystemPlugin : AimpPlugin
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
            ExtensionFileInfo fileInfo = new ExtensionFileInfo();

            Player.Core.RegisterExtension(fileSystem);
            if (Player.Core.RegisterExtension(fileInfo) != AimpActionResult.Ok)
            {
                System.Diagnostics.Debugger.Break();
            }

            //var g = Guid.NewGuid();
            //var ptr = Player.Core.CreateObject(ref g);
            //IAimpString str = (IAimpString)Marshal.GetObjectForIUnknown(ptr);
            //str.SetData("test", 4);
            //var a = str.GetLength();
            //try
            //{
            //    var s = str.GetData();
            //}
            //catch (Exception e)
            //{

            //}
        }

        private void Item_OnExecute(object sender, System.EventArgs e)
        {
            var dir = Environment.GetFolderPath(Environment.SpecialFolder.MyMusic);
            var files = Directory.GetFiles(dir, "*.mp3");

            var filesToPlaylist = files
                .Where(file => Player.ServiceFileFormats.IsSupported(file, FileManager.FileFormats.AIMP_SERVICE_FILEFORMATS_CATEGORY_AUDIO) == AimpActionResult.Ok)
                .Select(f => $"{CustomFileSystem.sMySchemePrefix}{f}").ToList();
            if (filesToPlaylist.Any())
            {
                if (Player.PlaylistManager.GetActivePlaylist(out var activePl) == AimpActionResult.Ok)
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
