using System;
using System.Windows.Forms;
using AIMP.SDK;

namespace dotnet_ExtendDialogWindow
{
    [AimpPlugin("dotnet_ExtendDialogWindow", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons)]
    public class AimpExtendDialogWindowPlugin : AimpPlugin, IAimpExternalSettingsDialog
    {
        public override void Initialize()
        {
            var optionsForm = new OptionsFrame(Player);
            Player.Core.RegisterExtension(optionsForm);
        }

        public override void Dispose()
        {
            
        }

        public void Show(IntPtr parentWindow)
        {
            MessageBox.Show("AimpExtendDialogWindowPlugin.Show");
        }
    }
}
