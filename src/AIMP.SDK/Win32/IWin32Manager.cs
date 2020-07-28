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

    /// <summary>
    /// Interface IWin32Manager
    /// </summary>
    public interface IWin32Manager
    {
        /// <summary>
        /// Gets the aimp handle.
        /// </summary>
        /// <returns>IntPtr.</returns>
        IntPtr GetAimpHandle();

        /// <summary>
        /// Sets the parent window.
        /// </summary>
        /// <param name="child">The child.</param>
        /// <param name="parent">The parent.</param>
        void SetParentWindow(IntPtr child, IntPtr parent);

        /// <summary>
        /// Gets the window position.
        /// </summary>
        /// <param name="handle">The handle.</param>
        /// <returns>Point.</returns>
        Point GetWindowPosition(IntPtr handle);
    }
}