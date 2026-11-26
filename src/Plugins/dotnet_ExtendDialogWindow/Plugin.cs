using System;
using System.Windows.Forms;
using AIMP;
using AIMP.SDK;

namespace dotnet_ExtendDialogWindow
{
    [AimpPlugin("dotnet_ExtendDialogWindow", "Evgeniy Bogdan", "1.0.0.0", AimpPluginType = AimpPluginType.Addons)]
    public class Plugin : AimpPlugin, IAimpExternalSettingsDialog
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
