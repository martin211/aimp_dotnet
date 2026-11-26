using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Options
{
    /// <summary>
    /// <c>IAIMPServiceOptionsDialog</c> (apiOptions.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764F-7074-446C67000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceOptionsDialogNative
    {
        [PreserveSig]
        int FrameModified(IntPtr frame);

        [PreserveSig]
        int FrameShow(IntPtr frame, int forceShow);
    }
}