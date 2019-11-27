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
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Playlist;

namespace DemoPlugin
{
    public partial class PlayListControl : UserControl
    {
        private readonly IAimpPlayer _player;
        private readonly IAimpPlaylist _playList;

        public PlayListControl(IAimpPlaylist playList, IAimpPlayer player)
        {
            InitializeComponent();

            listView1.Columns.Add("trackId", "#");
            listView1.Columns.Add("trackName", "Name");
            listView1.Columns.Add("Duration", "Duration");
            listView1.MultiSelect = false;
            listView1.HeaderStyle = ColumnHeaderStyle.Nonclickable;
            listView1.View = View.Details;

            listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            listView1.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);

            _playList = playList;
            _player = player;

            LoadTracks();

            playList.Changed += (sender, type) =>
            {
                if (type.HasFlag(PlaylistNotifyType.AIMP_PLAYLIST_NOTIFY_STATISTICS))
                {
                    RefreshTracks();
                }
            };
        }

        public void RefreshTracks()
        {
            listView1.Items.Clear();
            int count = _playList.GetItemCount();
            for (var i = 0; i < count; i++)
            {
                var item = _playList.GetItem(i);
                if (item == null)
                {
                    continue;
                }

                listView1.Items.Add(GetTrack(item));
            }
        }

        public void LoadTracks()
        {
            IList<string> files;
            if (Utils.CheckResult(_playList.GetFiles(PlaylistGetFilesFlag.All, out files)) == AimpActionResult.OK)
            {
                int count = _playList.GetItemCount();
                for (var i = 0; i < count; i++)
                {
                    var item = _playList.GetItem(i);
                    if (item == null)
                    {
                        continue;
                    }

                    listView1.Items.Add(GetTrack(item));
                }
            }
        }

        private ListViewItem GetTrack(IAimpPlaylistItem item)
        {
            var trackItem = new ListViewItem { Text = item.PlaybackIndex.ToString() };
            trackItem.SubItems.Add(item.DisplayText);
            trackItem.SubItems.Add(TimeSpan.FromSeconds(item.FileInfo.Duration).ToString());
            // save playlist item to tag.
            trackItem.Tag = item;

            return trackItem;
        }

        private void toolStripMenuItem1_Click(object sender, System.EventArgs e)
        {
            _playList.Delete(PlaylistDeleteFlags.AIMP_PLAYLIST_DELETE_FLAGS_PHYSICALLY, "test", FilterFunc);
        }

        private bool FilterFunc(IAimpPlaylistItem aimpPlaylistItem, object o)
        {
            return true;
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (listView1.SelectedItems.Count > 0)
            {
                var currentTrack = listView1.SelectedItems[0].Tag as IAimpPlaylistItem;
                TagEditorForm form = new TagEditorForm(currentTrack, _player);
                form.ShowDialog(this);
            }
        }
    }
}
