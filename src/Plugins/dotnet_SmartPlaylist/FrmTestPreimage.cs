using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace Aimp.DotNet.SmartPlaylist
{
    public partial class FrmTestPreimage : Form, IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        private readonly IAimpPlaylistManager2 _manager;
        private readonly IAimpCore _core;
        private readonly TestPreimageFactory _factory;
        private readonly IList<string> _playlists;

        public FrmTestPreimage()
        {
            InitializeComponent();
        }

        public FrmTestPreimage(IAimpPlaylistManager2 manager, IAimpCore core)
            : this()
        {
            _manager = manager;
            _core = core;
            _playlists = new List<string>();

            _factory = new TestPreimageFactory();
            _core.RegisterExtension(this);
            _core.RegisterExtension(_factory);

            for (int i = 0; i < _manager.GetLoadedPlaylistCount(); i++)
            {
                IAimpPlaylist pl;
                if (_manager.GetLoadedPlaylist(i, out pl) == AimpActionResult.Ok)
                {
                    PlAdded(pl);
                }
            }
        }

        private void PlAdded(IAimpPlaylist pl)
        {
            _playlists.Add($"{pl.Id};{pl.Name}");
        }

        private void PlRemoved(IAimpPlaylist pl)
        {
            _playlists.Remove($"{pl.Id};{pl.Name}");
        }

        private void SetPlaylistPreimage(IAimpPlaylist pl, IAimpPlaylistPreimage preimage)
        {
            pl.PreImage = preimage;
        }

        private IAimpPlaylistPreimage GetPlaylistPreimage(IAimpPlaylist pl)
        {
            return pl.PreImage;
        }

        private IAimpPlaylist GetSelectedPlaylist()
        {
            return null;
        }

        public event PlayListHandler PlaylistActivated;
        public event PlayListHandler PlaylistAdded;
        public event PlayListHandler PlaylistRemoved;
        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            PlAdded(playlist);
            return AimpActionResult.Ok;
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            PlRemoved(playlist);
            return AimpActionResult.Ok;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();
            if (pl != null)
            {
                SetPlaylistPreimage(pl, null);
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();
            if (pl != null)
            {
                var pi = GetPlaylistPreimage(pl);
                if (pi != null)
                {
                    SetPlaylistPreimage(pl, pi);
                    pl.ReloadFromPreimage();
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();
            if (pl != null)
            {
                if (_manager.GetPreimageFactoryByID(Constants.PreimageFactory.FoldersId, out var factory) == AimpActionResult.Ok)
                {
                    factory.CreatePreimage(out var preimage);
                    if (preimage is IAimpPlaylistPreimageFolders filePreimage)
                    {
                        filePreimage.AutoSync = true;
                        filePreimage.ItemsAdd(Environment.GetFolderPath(Environment.SpecialFolder.MyMusic), true);
                        SetPlaylistPreimage(pl, filePreimage);
                    }
                }
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();
            if (pl != null)
            {
                var pi = GetPlaylistPreimage(pl);
                if (pi != null)
                {
                    var stream = _core.CreateStream();
                    pi.ConfigSave(stream);
                    //pi.Reset() TODO
                    stream.Seek(0, SeekOrigin.Begin);
                    pi.ConfigLoad(stream);
                }
            }
        }
    }
}
