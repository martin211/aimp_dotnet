using System;
using AIMP.SDK.Options;

namespace DemoPlugin.OptionsFrame
{
    public class OptionsDialogFrame : IAimpOptionsDialogFrame
    {
        private SettingsForm _settingsForm;

        public string GetName()
        {
            return "Demo Plugin";
        }

        public IntPtr CreateFrame(IntPtr parentWindow)
        {
            _settingsForm = new SettingsForm();
            _settingsForm.Show(parentWindow);
            return _settingsForm.Handle;

        }

        public void DestroyFrame()
        {
            _settingsForm.Hide();
        }

        public void Notification(OptionsDialogFrameNotificationType id)
        {
        }
    }
}