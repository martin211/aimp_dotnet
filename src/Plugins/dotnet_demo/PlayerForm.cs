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
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Playlist;
using DemoPlugin.UI;

namespace DemoPlugin
{
    public partial class PlayerForm : Form
    {
        private readonly IAimpPlayer _aimpPlayer;

        private readonly LoggerForm _loggerForm;
        private List<IAimpPlaylist> _playLists;

        public PlayerForm(IAimpPlayer player)
        {
            _playLists = new List<IAimpPlaylist>();
            _aimpPlayer = player;
            InitializeComponent();

            _loggerForm = new LoggerForm();

            _aimpPlayer.Core.CoreMessage += (param1, param2) =>
            {
                if (param1 == AimpMessages.AimpCoreMessageType.AIMP_MSG_EVENT_PLAYABLE_FILE_INFO)
                {
                    var cover = _aimpPlayer.CurrentFileInfo.AlbumArt;
                    if (cover != null)
                    {
                        pictureBox1.Image = cover;
                    }
                }
            };

            Load += OnActivated;

       //_aimpPlayer.PlaylistManager.PlaylistActivated += (name, id) =>
            //{
            //    Logger.Instance.AddInfoMessage($"[Event] PlayListManager.PlaylistActivated: {name} {id}");

            //    foreach (var tabPage in tabPlayLists.TabPages)
            //    {
            //        var tp = tabPage as TabPage;
            //        if (tp != null && tp.Tag.Equals(id))
            //        {
            //            tabPlayLists.SelectTab(tp);
            //            break;
            //        }
            //    }
            //};

            //_aimpPlayer.PlaylistManager.PlaylistAdded += (name, id) =>
            //{
            //    Logger.Instance.AddInfoMessage($"[Event] PlayListManager.PlaylistAdded: {name} {id}");

            //    IAimpPlaylist pl;
            //    if (_aimpPlayer.PlaylistManager.GetLoadedPlaylistById(id, out pl) == AimpActionResult.Ok)
            //    {
            //        AddPlayListTab(id, name, pl);
            //    }
            //};

            //_aimpPlayer.PlaylistManager.PlaylistRemoved += (name, id) =>
            //{
            //    Logger.Instance.AddInfoMessage($"[Event] PlayListManager.PlaylistRemoved: {name} {id}");

            //    foreach (var tabPage in tabPlayLists.TabPages)
            //    {
            //        var tp = tabPage as TabPage;
            //        if (tp != null && tp.Tag.Equals(id))
            //        {
            //            tabPlayLists.TabPages.Remove(tp);
            //            break;
            //        }
            //    }
            //};

            _aimpPlayer.PlaylistManager.PlaylistQueue.ContentChanged += (sender) =>
            {
                Logger.Instance.AddInfoMessage($"[Event] PlaylistQueue.ContentChanged");
            };

            _aimpPlayer.PlaylistManager.PlaylistQueue.StateChanged += (sender) =>
            {
                Logger.Instance.AddInfoMessage($"[Event] PlaylistQueue.StateChanged");
            };

            _aimpPlayer.StateChanged += (sender, args) =>
            {
                Logger.Instance.AddInfoMessage($"[Event] AimpPlayer.StateChanged: {args.PlayerState}");

                switch (args.PlayerState)
                {
                    case AimpPlayerState.Stopped:
                        Text = "State: stopped";
                        break;
                    case AimpPlayerState.Pause:
                        Text = "State: pause";
                        break;
                    case AimpPlayerState.Playing:
                        Text = "State: playing";
                        break;
                }
            };
        }

        public new void Dispose()
        {
            base.Dispose();
        }

        private void AddPlayListTab(string id, string name, IAimpPlaylist playList)
        {
            var tab = new TabPage(id)
            {
                Text = name,
                Tag = playList
            };

            var pl = new PlayListControl(playList, _aimpPlayer);
            tab.Controls.Add(pl);
            tabPlayLists.TabPages.Add(tab);

            playList.Activated += sender =>
            {
                tabPlayLists.SelectedTab = tab;
            };
        }

        private void TracksOnDoubleClick(object sender, EventArgs eventArgs)
        {
            var trackItem = (IAimpPlaylistItem)(sender as ListView).SelectedItems[0].Tag;
            _aimpPlayer.Play(trackItem);
        }

        private void OnActivated(object sender, EventArgs eventArgs)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            _aimpPlayer.Core.SendMessage(AimpMessages.AimpCoreMessageType.AIMP_MSG_CMD_SHOW_NOTIFICATION, 0, "Play Play Play");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            _aimpPlayer.Stop();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            _aimpPlayer.Pause();
        }

        private void trackBar2_Scroll(object sender, EventArgs e)
        {
            int v = trackBar2.Value;
            _aimpPlayer.Volume = (float)v/10;
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            _aimpPlayer.Position = trackBar1.Value;
        }

        private void button4_Click(object sender, EventArgs e)
        {
            _aimpPlayer.IsMute = !_aimpPlayer.IsMute;
        }

        private void button5_Click(object sender, EventArgs e)
        {
            _aimpPlayer.GoToPrev();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            _aimpPlayer.GoToNext();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            IAimpPlaylist pl;
            if (_aimpPlayer.PlaylistManager.GetActivePlaylist(out pl) == AimpActionResult.Ok)
            {
                pl.Sort("test", (item, playlistItem, arg3) => PlaylistSortComapreResult.TheSame);
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            var frm = new PlaylistEditor();
            if (frm.ShowDialog(this) == DialogResult.OK)
            {
                IAimpPlaylist playList;
                if (_aimpPlayer.PlaylistManager.CreatePlaylist(frm.PlaylistName, true, out playList) == AimpActionResult.Ok)
                {
                    _playLists.Add(playList);

                    //CheckResult(playList.Add("http://xstream1.somafm.com:2800", PlaylistFlags.NOEXPAND, PlaylistFilePosition.EndPosition));
                    //CheckResult(playList.AddList(new List<string>()
                    //{
                    //    "http://xstream1.somafm.com:2800",
                    //    "http://xstream1.somafm.com:2800"
                    //}, PlaylistFlags.NOEXPAND, PlaylistFilePosition.EndPosition));

                    //playList.Activated += o => { System.Diagnostics.Debug.WriteLine("Activated {0}", o.Name); };
                    playList.Changed += PlayListOnChanged;
                    playList.Activated += playlist =>
                    {
                        Logger.Instance.AddInfoMessage($"[Event] IAimpPlaylist.Activated: {playlist.Id} {playlist.Name}");
                    };
                    playList.Removed += playlist =>
                    {
                        Logger.Instance.AddInfoMessage($"[Event] IAimpPlaylist.Removed: {playlist.Id} {playlist.Name}");
                    };
                    playList.ScanningBegin += playlist =>
                    {
                        Logger.Instance.AddInfoMessage($"[Event] IAimpPlaylist.ScanningBegin: {playlist.Id} {playlist.Name}");
                    };
                    playList.ScanningEnd += (playlist, args) =>
                    {
                        Logger.Instance.AddInfoMessage($"[Event] IAimpPlaylist.ScanningEnd: {playlist.Id} {playlist.Name}");
                    };
                    playList.ScanningProgress += (playlist, args) =>
                    {
                        Logger.Instance.AddInfoMessage($"[Event] IAimpPlaylist.ScanningProgress: {playlist.Id} {playlist.Name}");
                    };
                }
            }
        }

        private void PlayListOnChanged(IAimpPlaylist sender, PlaylistNotifyType notifType)
        {
            Logger.Instance.AddInfoMessage($"[Event] IAimpPlaylist.Changed: {sender.Id} {sender.Name}");
            if (notifType.HasFlag(PlaylistNotifyType.AIMP_PLAYLIST_NOTIFY_STATISTICS))
            {
                
            }
        }

        private void button9_Click(object sender, EventArgs e)
        {
            IAimpPlaylist playList;
            if (_aimpPlayer.PlaylistManager.GetActivePlaylist(out playList) == AimpActionResult.Ok)
            {
                playList?.Close(PlaylistCloseFlag.ForceRemove);
            }
        }

        private void toolStripMenuItem1_Click(object sender, EventArgs e)
        {
            _loggerForm.Show(this);
        }

        private void button10_Click(object sender, EventArgs e)
        {
            //IAimpPlaylistItem item;
            //if (_aimpPlayer.PlayListManager.PlaylistQueue.GetItem(0, out item) == AimpActionResult.Ok)
            //{

            //}

            //_aimpPlayer.PlayListManager.PlaylistQueue.StateChanged += PlayListQueue_StateChanged;

            //var i = _aimpPlayer.PlayListManager.PlaylistQueue.Count();
        }

        private void PlayListQueue_StateChanged(object sender, EventArgs e)
        {
            
        }

        private void tabPlayLists_TabIndexChanged(object sender, EventArgs e)
        {

        }

        private void tabPlayLists_SelectedIndexChanged(object sender, EventArgs e)
        {
            var playlist = tabPlayLists.SelectedTab.Tag as IAimpPlaylist;
            if (playlist != null)
            {
                _aimpPlayer.PlaylistManager.SetActivePlaylist(playlist);
            }
        }

        private void PlayerForm_Shown(object sender, EventArgs e)
        {
            var count = _aimpPlayer.PlaylistManager.GetLoadedPlaylistCount();
            for (var i = 0; i < count; i++)
            {
                if (_aimpPlayer.PlaylistManager.GetLoadedPlaylist(i, out var playlist) == AimpActionResult.Ok && _playLists.All(c => c.Id != playlist.Id))
                {
                    AddPlayListTab(playlist.Id, playlist.Name, playlist);
                }
            }
        }
    }
}
