using System;
using System.Drawing;

namespace AIMP.SDK.Win32;

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