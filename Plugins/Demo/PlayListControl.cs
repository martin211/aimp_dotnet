using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AIMP.SDK.PlayList;

namespace DemoPlugin
{
    public partial class PlayListControl : UserControl
    {
        private readonly IAimpPlayList _playList;

        public PlayListControl(IAimpPlayList playList)
        {
            InitializeComponent();

            listView1.Columns.Add("trackId", "#");
            listView1.Columns.Add("trackName", "Name");
            listView1.MultiSelect = false;
            listView1.HeaderStyle = ColumnHeaderStyle.Nonclickable;
            listView1.View = View.Details;

            _playList = playList;

            playList.Changed += (sender, type) =>
            {
                if (type.HasFlag(PlayListNotifyType.AIMP_PLAYLIST_NOTIFY_STATISTICS))
                {
                    LoadTracks();
                }
            };
        }

        public void LoadTracks()
        {
            for (var i = 0; i < _playList.GetItemCount(); i++)
            {
                var item = _playList.GetItem(i);
                if (item == null)
                {
                    continue;
                }

                var trackItem = new ListViewItem { Text = item.Index.ToString() };
                trackItem.SubItems.Add(item.DisplayText);
                // save playlist item to tag.
                trackItem.Tag = item;

                listView1.Items.Add(trackItem);

                item = null;
            }
        }
    }
}
