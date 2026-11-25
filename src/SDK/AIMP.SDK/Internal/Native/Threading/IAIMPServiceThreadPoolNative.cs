using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Threading
{
    /// <summary>
    /// <c>IAIMPServiceThreadPool</c> (apiDepricated.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7654-6872-64506F6F6C00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceThreadPoolNative
    {
        [PreserveSig]
        int Cancel(UIntPtr taskHandle, uint flags);

        [PreserveSig]
        int Execute(IntPtr task, out UIntPtr taskHandle);

        [PreserveSig]
        int WaitFor(UIntPtr taskHandle);
    }
}