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
using AIMP.SDK;

namespace Aimp.DotNet.SmartPlaylist
{
    [AimpPlugin("SmartPlaylistDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons,
        FullDescription = "Smart Playlist demo plugin")]
    public class SmartPlaylistPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            var listner = new FrmTestPreimage(Player.ServicePlaylistManager, Player.Core);
            listner.Show();
        }

        public override void Dispose()
        {
        }
    }
}
