using System;
using System.Windows.Forms;

namespace DemoPlugin
{
    public partial class LoggerForm : Form
    {
        public LoggerForm()
        {
            InitializeComponent();
        }

        public void WriteLog(string message)
        {
            textBox1.Text += $"{message}{Environment.NewLine}";
        }
    }
}
