namespace AIMP.SDK.Services.Win32Manager
{
    using System;

    public interface IWin32Manager
    {
        void SetParentWindow(IntPtr child, IntPtr parent);
    }
}