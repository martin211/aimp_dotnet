using System;
using AIMP.SDK.Services;
using AIMP.SDK.Services.Options;

namespace TestPlugin
{
    public class OptionsFrame : IAimpOptionsDialogFrame
    {
        public string GetName()
        {
            return "Demo plugin";
        }

        public IntPtr CreateFrame(IntPtr parentWindow)
        {
            return IntPtr.Zero;
        }

        public void DestroyFrame()
        {
            
        }

        public event AimpOptionFrameHandler Notification;
    }
}