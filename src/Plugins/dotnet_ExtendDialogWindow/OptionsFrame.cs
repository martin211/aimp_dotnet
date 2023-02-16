//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using AIMP.SDK;
using AIMP.SDK.Options;

namespace dotnet_ExtendDialogWindow
{
    public class OptionsFrame : IAimpOptionsDialogFrame, IAimpOptionsDialogFrameKeyboardHelper2, IDisposable
    {
        private IAimpPlayer _player;
        private SettingsForm _settingsForm;

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

        public void Notification(OptionsDialogFrameNotificationType id)
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

        public bool SelectNextControl(bool findForward, bool isTabKeyAction)
        {
            throw new NotImplementedException();
        }

        public bool SelectLastControl()
        {
            throw new NotImplementedException();
        }

        public void Dispose()
        {
            _settingsForm?.Dispose();
        }
    }
}
