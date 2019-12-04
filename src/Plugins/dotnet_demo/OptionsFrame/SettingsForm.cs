using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace DemoPlugin.OptionsFrame
{
    public partial class SettingsForm : Form
    {
        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        public SettingsForm()
        {
            InitializeComponent();
        }

        public void Show(IntPtr parent)
        {
            SetParent(Handle, parent);
            WindowState = FormWindowState.Maximized;
            Show();
        }
    }
}
