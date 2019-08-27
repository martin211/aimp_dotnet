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
using System.Windows.Forms;
using AIMP.SDK;

namespace dotnet_ExtendDialogWindow
{
    [AimpPlugin("dotnet_ExtendDialogWindow", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons)]
    public class AimpExtendDialogWindowPlugin : AimpPlugin, IAimpExternalSettingsDialog
    {
        public void Show(IntPtr parentWindow)
        {
            MessageBox.Show("AimpExtendDialogWindowPlugin.Show");
        }

        public override void Initialize()
        {
            var optionsForm = new OptionsFrame(Player);
            Player.Core.RegisterExtension(optionsForm);
        }

        public override void Dispose()
        {
            
        }
    }
}
