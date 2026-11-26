using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Core
{
    /// <summary>
    /// <c>IAIMPServiceShutdown</c> (apiCore.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7653-6875-74646F776E00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceShutdownNative
    {
        [PreserveSig]
        int Restart(IntPtr parameters);

        [PreserveSig]
        int Shutdown(uint flags);
    }
}