using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace AIMP.DotNet.MusicLibrary.SmartPlaylist
{
    public class FrmTestPreimage : IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        protected List<IAimpPlaylist> AimpPlaylists { get; set; }
        private readonly IAimpPlaylistManager2 _manager;

        public event PlayListHandler PlaylistActivated;
        public event PlayListHandler PlaylistAdded;
        public event PlayListHandler PlaylistRemoved;

        public FrmTestPreimage(IAimpPlaylistManager2 service, IAimpCore core)
        {
            _manager = service;
            var factory = new TestPreimageFactory();
            AimpPlaylists = new List<IAimpPlaylist>();
            core.RegisterExtension(this);
            core.RegisterExtension(factory);

            for (int i = 0; i < service.GetLoadedPlaylistCount(); i++)
            {
                IAimpPlaylist pl;
                if (service.GetLoadedPlaylist(i, out pl) == AimpActionResult.Ok)
                {
                    //PlaylistAdded?.Invoke(pl.Name, pl.Id);
                    AimpPlaylists.Add(pl);
                }
            }
        }

        public IAimpPlaylist GetSelectedPlaylist()
        {
            if (AimpPlaylists.Count > 0)
            {
                //_manager.GetLoadedPlaylistById()
            }
            return null;
        }

        public IAimpPlaylistPreimage GetPlaylistPreimage(IAimpPlaylist playlist)
        {
            return playlist.PreImage;
        }

        public void SetPlaylistPreimage(IAimpPlaylist playlist, IAimpPlaylistPreimage preimage)
        {
            playlist.PreImage = preimage;
        }
    }
}