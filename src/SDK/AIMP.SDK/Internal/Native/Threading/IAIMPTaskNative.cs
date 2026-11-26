using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Threading
{
    /// <summary>
    /// <c>IAIMPTask</c> (apiThreading.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5461-736B-3200-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPTaskNative
    {
        [PreserveSig]
        void Execute(IntPtr owner);
    }
}