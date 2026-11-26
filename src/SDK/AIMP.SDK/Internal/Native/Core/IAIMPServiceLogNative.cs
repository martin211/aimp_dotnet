using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Core
{
    /// <summary>
    /// <c>IAIMPServiceLog</c> (apiCore.h, AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764C-6F67-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceLogNative
    {
        [PreserveSig]
        void Add1(IntPtr text, uint flags);

        [PreserveSig]
        void Add2(IntPtr text, uint flags);
    }
}