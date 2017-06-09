using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DemoPlugin.UI
{
    public partial class PlaylistEditor : Form
    {
        public PlaylistEditor()
        {
            InitializeComponent();
        }

        public string PlaylistName => textBox1.Text;
    }
}
