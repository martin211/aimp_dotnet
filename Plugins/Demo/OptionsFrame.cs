using System;
using AIMP.SDK;
using AIMP.SDK.Services.Player;
using DemoPlugin;

namespace TestPlugin
{
    public class OptionsFrame : AimpOptionsDialogFrame
    {
        private SettingsForm _settingsForm;
        private IAimpPlayer _player;

        public OptionsFrame(IAimpPlayer player)
        {
            _player = player;
        }

        public override string GetName()
        {
            return "Demo plugin";
        }

        public override IntPtr CreateFrame(IntPtr parentWindow)
        {
            _settingsForm = new SettingsForm(parentWindow, _player, this);
            _settingsForm.Show();
            return _settingsForm.Handle;
        }

        public override void DestroyFrame()
        {
            _settingsForm.Hide();
            _settingsForm = null;
        }

        public override void Notification(int id)
        {
        }

        public override bool DialogKey(int charCode)
        {
            return true;
        }

        public override bool SelectFirstControl()
        {
            return true;
        }

        public override bool SelectNextControl(int findForward, int isTabKeyAction)
        {
            return true;
        }
    }
}