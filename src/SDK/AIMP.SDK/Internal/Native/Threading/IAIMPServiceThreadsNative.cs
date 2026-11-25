using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Threading
{
    /// <summary>
    /// <c>IAIMPServiceThreads</c> (apiThreading.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7654-6872-656164730000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceThreadsNative
    {
        [PreserveSig]
        int ExecuteInMainThread(IntPtr task, uint flags);

        [PreserveSig]
        int ExecuteInThread(IntPtr task, out UIntPtr taskHandle);

        [PreserveSig]
        int Cancel(UIntPtr taskHandle, uint flags);

        [PreserveSig]
        int WaitFor(UIntPtr taskHandle);
    }
}