using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// Native projection of <c>IAIMPConfig</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-436F-6E66-6967-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPConfigNative
    {
        [PreserveSig]
        int Delete(IntPtr keyPath);

        [PreserveSig]
        int GetValueAsFloat(IntPtr keyPath, out double value);

        [PreserveSig]
        int GetValueAsInt32(IntPtr keyPath, out int value);

        [PreserveSig]
        int GetValueAsInt64(IntPtr keyPath, out long value);

        [PreserveSig]
        int GetValueAsStream(IntPtr keyPath, out IntPtr value);

        [PreserveSig]
        int GetValueAsString(IntPtr keyPath, out IntPtr value);

        [PreserveSig]
        int SetValueAsFloat(IntPtr keyPath, double value);

        [PreserveSig]
        int SetValueAsInt32(IntPtr keyPath, int value);

        [PreserveSig]
        int SetValueAsInt64(IntPtr keyPath, long value);

        [PreserveSig]
        int SetValueAsStream(IntPtr keyPath, IntPtr value);

        [PreserveSig]
        int SetValueAsString(IntPtr keyPath, IntPtr value);
    }
}