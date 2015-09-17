using System;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Interfaces;
using AIMP.SDK.Services.PlayListManager;

namespace TestPlugin
{
    using System.Collections.Generic;

    using AIMP.SDK.Services.Player;

    public partial class Form1 : Form
    {
        private readonly IAimpPlayer _aimpPlayer;

        public Form1(IAimpPlayer player)
        {
            _aimpPlayer = player;
            InitializeComponent();
            _aimpPlayer.TrackChanged += (sender, args) =>
                {
                    pictureBox1.Image = _aimpPlayer.CurrentFileInfo.AlbumArt;
                };

            Load += OnActivated;

            _aimpPlayer.PlayListManager.PlaylistActivated += (name, id) =>
            {

            };

            _aimpPlayer.PlayListManager.PlaylistAdded += (name, id) =>
            {
                var pl = _aimpPlayer.PlayListManager.GetLoadedPlaylistById(id);
                AddPlayListTab(id, name, pl);
            };

            _aimpPlayer.PlayListManager.PlaylistRemoved += (name, id) =>
            {
                foreach (var tabPage in tabPlayLists.TabPages)
                {
                    var tp = tabPage as TabPage;
                    if (tp != null && tp.Tag.Equals(id))
                    {
                        tabPlayLists.TabPages.Remove(tp);
                        break;
                    }
                }
            };
        }

        private void AddPlayListTab(string id, string name, IAimpPlayList playList)
        {
            var tab = new TabPage(id)
            {
                Text = name,
                Tag = id
            };

            var tracks = new ListView()
            {
                Dock = DockStyle.Fill
            };

            tracks.Columns.Add("trackId", "#");
            tracks.Columns.Add("trackName", "Name");
            tracks.MultiSelect = false;
            tracks.HeaderStyle = ColumnHeaderStyle.Nonclickable;
            tracks.View = View.Details;

            tracks.DoubleClick += TracksOnDoubleClick;

            tab.Controls.Add(tracks);

            for (var i = 0; i < playList.GetItemCount(); i++)
            {
                var item = playList.GetItem(i);
                var trackItem = new ListViewItem {Text = item.Index.ToString()};
                trackItem.SubItems.Add(item.DisplayText);
                // save playlist item to tag.
                trackItem.Tag = item;

                tracks.Items.Add(trackItem);
            }

            tabPlayLists.TabPages.Add(tab);
        }

        private void TracksOnDoubleClick(object sender, EventArgs eventArgs)
        {
            var trackItem = (IAimpPlayListItem)(sender as ListView).SelectedItems[0].Tag;
            _aimpPlayer.Play(trackItem);
        }

        private void OnActivated(object sender, EventArgs eventArgs)
        {
            var playlistCount = _aimpPlayer.PlayListManager.GetLoadedPlaylistCount();
            for (var i = 0; i < playlistCount; i++)
            {
                var playList = _aimpPlayer.PlayListManager.GetLoadedPlaylist(i);
                AddPlayListTab(playList.Id, playList.Name, playList);
            }
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
            _aimpPlayer.Volume =  (float) v/10;
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
            var pl = _aimpPlayer.PlayListManager.GetActivePlaylist();
            pl.Sort((item1, item2) =>
            {
                return PlayListSortComapreResult.TheSame;
            });
        }

        private void button8_Click(object sender, EventArgs e)
        {
            var playList = _aimpPlayer.PlayListManager.CreatePlaylist("Test play list", true);
            playList.Add("http://xstream1.somafm.com:2800", PlayListFlags.NOEXPAND, PlayListFilePosition.EndPosition);
            playList.AddList(new List<string>()
                                 {
                                    "http://xstream1.somafm.com:2800",
                                    "http://xstream1.somafm.com:2800"
                                 }, PlayListFlags.NOEXPAND, PlayListFilePosition.EndPosition);
            playList.Activated += (o) =>
                {
                    System.Diagnostics.Debug.WriteLine("Activated {0}", o.Name); 
                };

            playList.Changed += (list, type) =>
                {
                    System.Diagnostics.Debug.WriteLine(type);
                };
        }
    }
}
