using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Threading
{
    /// <summary>
    /// <c>IAIMPServiceSynchronizer</c> (apiDepricated.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7653-796E-637200000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceSynchronizerNative
    {
        [PreserveSig]
        int ExecuteInMainThread(IntPtr task, int executeNow);
    }
}