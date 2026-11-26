using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Actions
{
    /// <summary>
    /// <c>IAIMPActionEvent</c> (apiActions.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4163-7469-6F6E-4576656E7400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPActionEventNative
    {
        [PreserveSig]
        void OnExecute(IntPtr data);
    }
}