using System;
using AIMP.SDK.Options;
using AIMP.SDK.Player;

namespace dotnet_ExtendDialogWindow
{
    public class OptionsFrame : IAimpOptionsDialogFrame, IAimpOptionsDialogFrameKeyboardHelper
    {
        private SettingsForm _settingsForm;
        private IAimpPlayer _player;

        public OptionsFrame(IAimpPlayer player)
        {
            _player = player;
        }

        public string GetName()
        {
            return "Demo plugin";
        }

        public IntPtr CreateFrame(IntPtr parentWindow)
        {
            _settingsForm = new SettingsForm(parentWindow, _player, this);
            _settingsForm.Show();
            return _settingsForm.Handle;
        }

        public void DestroyFrame()
        {
            _settingsForm.Hide();
            _settingsForm = null;
        }

        public void Notification(int id)
        {
        }

        public bool DialogKey(int charCode)
        {
            return true;
        }

        public bool SelectFirstControl()
        {
            return true;
        }

        public bool SelectNextControl(int findForward, int isTabKeyAction)
        {
            return true;
        }
    }
}