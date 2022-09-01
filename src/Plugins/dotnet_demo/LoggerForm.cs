//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Windows.Forms;

namespace DemoPlugin
{
    public partial class LoggerForm : Form
    {
        public LoggerForm()
        {
            InitializeComponent();
            Logger.Instance.OnLogChanged += (sender, s) => { textBox1.Text += $"{s}{Environment.NewLine}"; };
        }

        public void WriteLog(string message)
        {
            textBox1.Text += $"{message}{Environment.NewLine}";
        }
    }
}
