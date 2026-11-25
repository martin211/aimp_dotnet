using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// <c>IAIMPErrorInfo</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4572-7249-6E66-6F0000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPErrorInfoNative
    {
        [PreserveSig]
        int GetInfo(out int errorCode, out IntPtr message, out IntPtr details);

        [PreserveSig]
        int GetInfoFormatted(out IntPtr text);

        [PreserveSig]
        void SetInfo(int errorCode, IntPtr message, IntPtr details);
    }
}