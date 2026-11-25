using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Core
{
    /// <summary>
    /// Native projection of <c>IAIMPCore</c> (apiCore.h).
    /// Vtable order MUST match the SDK header exactly.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-436F-7265-0000-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPCoreNative
    {
        [PreserveSig]
        int CreateObject(in Guid iid, out IntPtr instance);

        [PreserveSig]
        int GetPath(int pathId, out IntPtr value);

        [PreserveSig]
        int RegisterExtension(in Guid serviceIid, IntPtr extension);

        [PreserveSig]
        int RegisterService(IntPtr service);

        [PreserveSig]
        int UnregisterExtension(IntPtr extension);
    }
}