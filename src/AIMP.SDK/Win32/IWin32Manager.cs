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