using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MUIManager
{
    /// <summary>
    /// <c>IAIMPServiceMUI</c> (apiMUI.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764D-5549-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceMUINative
    {
        [PreserveSig]
        int GetName(out IntPtr value);

        [PreserveSig]
        int GetValue(IntPtr keyPath, out IntPtr value);

        [PreserveSig]
        int GetValuePart(IntPtr keyPath, int part, out IntPtr value);
    }
}