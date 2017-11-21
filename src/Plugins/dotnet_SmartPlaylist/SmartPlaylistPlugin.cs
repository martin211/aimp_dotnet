using System;
using AIMP.SDK;

namespace Aimp.DotNet.SmartPlaylist
{
    [AimpPlugin("SmartPlaylistDemoPlugin", "Martin", "1.0.0", AimpPluginType = AimpPluginType.Addons, FullDescription = "Smart Playlist demo plugin")]
    public class SmartPlaylistPlugin : AimpPlugin
    {
        public override void Initialize()
        {
            var listner = new FrmTestPreimage(Player.PlaylistManager, Player.Core);
            listner.Show();
        }

        public override void Dispose()
        {

        }
    }
}
