using System;
using System.Diagnostics;
using System.Drawing;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Win32;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IWin32Manager"/>.
    /// </summary>
    internal sealed class AimpWin32Manager : AimpObjectWrapper, IWin32Manager
    {
        public IntPtr GetAimpHandle()
        {
            return Process.GetCurrentProcess().MainWindowHandle;
        }

        public void SetParentWindow(IntPtr child, IntPtr parent)
        {
        }

        public Point GetWindowPosition(IntPtr handle)
        {
            return Point.Empty;
        }
    }
}