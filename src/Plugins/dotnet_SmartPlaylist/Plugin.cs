//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP;
using AIMP.SDK;

namespace Aimp.DotNet.SmartPlaylist
{
    [AimpPlugin("SmartPlaylistDemoPlugin", "Evgeniy Bogdan", AdditionalInfo.Version, AimpPluginType = AimpPluginType.Addons,
        FullDescription = "Smart Playlist demo plugin")]
    public class Plugin : AimpPlugin
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
