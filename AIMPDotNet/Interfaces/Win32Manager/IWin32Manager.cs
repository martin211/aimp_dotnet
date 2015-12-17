namespace AIMP.SDK.Services.Win32Manager
{
    using System;
    using System.Drawing;

    public interface IWin32Manager
    {
        IntPtr GetAimpHandle();

        void SetParentWindow(IntPtr child, IntPtr parent);

        Point GetWindowPosition(IntPtr handle);
    }
}