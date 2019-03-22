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
using AIMP.SDK.Options;
using AIMP.SDK.Player;

namespace dotnet_ExtendDialogWindow
{
    public class OptionsFrame : IAimpOptionsDialogFrame, IAimpOptionsDialogFrameKeyboardHelper
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

        public bool SelectNextControl(int findForward, int isTabKeyAction)
        {
            return true;
        }
    }
}