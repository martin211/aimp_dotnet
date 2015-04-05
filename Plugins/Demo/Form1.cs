using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using AIMP.SDK.Interfaces;

namespace TestPlugin
{
    using AIMP.SDK.Services.AlbumArtManager;

    public partial class Form1 : Form
    {
        private readonly IAimpPlayer _aimpPlayer;

        public Form1(IAimpPlayer player)
        {
            _aimpPlayer = player;
            InitializeComponent();
            _aimpPlayer.TrackChanged += (sender, args) =>
                {
                    this.pictureBox1.Image = _aimpPlayer.CurrentFileInfo.AlbumArt;
                };
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
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
    }
}
