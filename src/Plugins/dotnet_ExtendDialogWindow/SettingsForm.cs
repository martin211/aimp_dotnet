// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using AIMP.SDK;
using AIMP.SDK.MUIManager;
using AIMP.SDK.Options;
using AIMP.SDK.Player;

namespace dotnet_ExtendDialogWindow
{
    internal partial class SettingsForm : Form
    {
        public static string _settingButtonText = "Options";

        private IAimpOptionsDialogFrame _parentFrame;

        private IAimpPlayer _player;

        public SettingsForm(IntPtr parentWindow, IAimpPlayer player, IAimpOptionsDialogFrame parentFrame)
            : this()
        {
            SetParent(Handle, parentWindow);
            _parentFrame = parentFrame;

            _player = player;
            Show();
            WindowState = FormWindowState.Maximized;
        }

        public SettingsForm()
        {
            InitializeComponent();
        }
        //public PluginSettings Settings { get; set; }

        [DllImport("user32.dll", SetLastError = true)]
        private static extern IntPtr SetParent(IntPtr hWndChild, IntPtr hWndNewParent);

        private void CbDebugModeOnCheckedChanged(object sender, EventArgs eventArgs)
        {
            //Settings.IsDebugMode = cbDebugMode.Checked;
        }

        private void SetLocaleText(IAimpMUIManager muiManager)
        {
            lCaption.Text = muiManager.GetValue("DotNet.Plugins\\Caption");
            tabPlugins.Text = muiManager.GetValue("DotNet.Plugins\\Plugins");

            var setText = muiManager.GetValue("DotNet.Plugins\\bSettings");
            if (!string.IsNullOrWhiteSpace(setText))
            {
                _settingButtonText = setText;
            }
        }

        private void SettingsForm_Load(object sender, EventArgs e)
        {
        }

        private void button1_Click(object sender, EventArgs e)
        {
            _player.ServiceOptionsDialog.FrameModified(_parentFrame);
        }

        internal class DisplayableForPlugins
        {
            public DisplayableForPlugins(PluginInformation pi)
            {
                plugInfo = pi;
            }

            public PluginInformation plugInfo { get; set; }

            public override string ToString()
            {
                return plugInfo.PluginInfo.Name + " v" + plugInfo.PluginInfo.Version +
                       " (" + plugInfo.PluginInfo.Author + ")\n" +
                       "[" + plugInfo.AssemblyFileName + "] " + plugInfo.PluginInfo.Description;
                ;
            }
        }
    }
}
