using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Core
{
    /// <summary>
    /// <c>IAIMPServiceVersionInfo</c> (apiCore.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7656-6572-496E666F0000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceVersionInfoNative
    {
        [PreserveSig]
        int FormatInfo(out IntPtr text);

        [PreserveSig]
        int GetBuildDate();

        [PreserveSig]
        int GetBuildState();

        [PreserveSig]
        int GetBuildNumber();

        [PreserveSig]
        int GetVersionID();
    }
}