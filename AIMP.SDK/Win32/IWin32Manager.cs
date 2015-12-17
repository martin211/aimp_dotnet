namespace AIMP.SDK.Win32
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