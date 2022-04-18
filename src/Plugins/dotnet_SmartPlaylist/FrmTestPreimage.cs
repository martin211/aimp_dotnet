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
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Playlist;
using AIMP.SDK.Playlist.Extensions;
using AIMP.SDK.Playlist.Objects;

namespace Aimp.DotNet.SmartPlaylist
{
    public partial class FrmTestPreimage : Form, IAimpExtensionPlaylistManagerListener, IAimpExtension
    {
        private readonly IAimpCore _core;
        private readonly TestPreimageFactory _factory;
        private readonly IAimpServicePlaylistManager _manager;
        private readonly IList<string> _playlists;

        public FrmTestPreimage()
        {
            InitializeComponent();
        }

        public FrmTestPreimage(IAimpServicePlaylistManager manager, IAimpCore core)
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
                var result = _manager.GetLoadedPlaylist(i);

                if (result.ResultType == ActionResultType.OK)
                {
                    PlAdded(result.Result);
                }
            }
        }

        public AimpActionResult OnPlaylistActivated(IAimpPlaylist playlist)
        {
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult OnPlaylistAdded(IAimpPlaylist playlist)
        {
            listView1.Items.Add(new ListViewItem
            {
                Text = playlist.Name,
                Tag = playlist.Id
            });
            return new AimpActionResult(ActionResultType.OK);
        }

        public AimpActionResult OnPlaylistRemoved(IAimpPlaylist playlist)
        {
            var item = listView1.Items.Cast<ListViewItem>().FirstOrDefault(c => c.Tag == playlist.Id);
            if (item != null)
            {
                listView1.Items.Remove(item);
            }

            return new AimpActionResult(ActionResultType.OK);
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
            if (listView1.SelectedItems.Count > 0)
            {
                var item = listView1.SelectedItems[0];
                var result = _manager.GetLoadedPlaylistById(item.Tag.ToString());
                return result.Result;
            }

            return null;
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
                    //SetPlaylistPreimage(pl, pi);
                    pl.ReloadFromPreimage();
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();
            if (pl != null)
            {
                var res = _manager.GetPreimageFactoryById(Constants.PreimageFactory.FoldersId);
                if (res.ResultType == ActionResultType.OK)
                {
                    var r = res.Result.CreatePreimage();
                    if (r.Result is IAimpPlaylistPreimageFolders filePreimage)
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
                    var stream = _core.CreateStream().Result;
                    pi.ConfigSave(stream);
                    //pi.Reset() TODO
                    stream.Seek(0, SeekOrigin.Begin);
                    pi.ConfigLoad(stream);
                }
            }
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();

            if (pl != null)
            {
                var preimage = GetPlaylistPreimage(pl);
                button1.Enabled = pl.PreImage != null;
                button2.Enabled = pl.PreImage != null;
                button3.Enabled = pl.PreImage == null;
                button4.Enabled = pl.PreImage != null;

                if (preimage != null)
                {
                    var type = preimage.FactoryId;
                    string preType = string.Empty;

                    if (preimage is IAimpPlaylistPreimageFolders)
                    {
                        preType = $"{type}(Folders)";
                    }
                    else if (preimage is IAimpPlaylistPreimage)
                    {
                        preType = $"{type}(Music Library)";
                    }

                    var handler = (IntPtr) GCHandle.Alloc(preimage);
                    label1.Text = $"Preimage: {preType} [{handler}]";
                }
                else
                {
                    label1.Text = "Playlist has no preimage";
                }
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            var pl = GetSelectedPlaylist();
            if (pl != null)
            {
                var preimage = GetPlaylistPreimage(pl);
                if (preimage != null)
                {
                    pl.ReloadFromPreimage();
                }
            }
        }
    }
}
