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
        }
    }
}
