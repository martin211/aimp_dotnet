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
using AIMP.SDK.Options;

namespace DemoPlugin.OptionsFrame
{
    public class OptionsDialogFrame : IAimpOptionsDialogFrame, IDisposable
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

        public void Dispose()
        {
            _settingsForm?.Dispose();
        }
    }
}
