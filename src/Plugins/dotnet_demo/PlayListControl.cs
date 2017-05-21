using System.Collections.Generic;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.Playlist;

namespace DemoPlugin
{
    public partial class PlayListControl : UserControl
    {
        private readonly IAimpPlaylist _playList;

        public PlayListControl(IAimpPlaylist playList)
        {
            InitializeComponent();

            listView1.Columns.Add("trackId", "#");
            listView1.Columns.Add("trackName", "Name");
            listView1.Columns.Add("Duration", "Duration");
            listView1.MultiSelect = false;
            listView1.HeaderStyle = ColumnHeaderStyle.Nonclickable;
            listView1.View = View.Details;

            _playList = playList;

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
            if (Utils.CheckResult(_playList.GetFiles(PlaylistGetFilesFlag.All, out files)) == AimpActionResult.Ok)
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
            trackItem.SubItems.Add(item.FileInfo.Duration.ToString("##:###"));
            // save playlist item to tag.
            trackItem.Tag = item;

            return trackItem;
        }
    }
}
