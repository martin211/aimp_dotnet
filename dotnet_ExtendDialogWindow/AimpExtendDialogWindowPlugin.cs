using System;
using System.Windows.Forms;
using AIMP.SDK;

namespace dotnet_ExtendDialogWindow
{
    [AimpPlugin("dotnet_ExtendDialogWindow", "AIMP DOTNET", "1", AimpPluginType = AimpPluginType.Addons)]
    public class AimpExtendDialogWindowPlugin : AimpPlugin
    {
        public override bool HasSettingDialog { get { return false; } }

        public override void Initialize()
        {
            var optionsForm = new OptionsFrame(Player);
            Player.Core.RegisterExtension(optionsForm);
        }

        public override void Dispose()
        {
            
        }

        public override void ShowSettingDialog(IWin32Window parentWindow)
        {
            
        }
    }
}
