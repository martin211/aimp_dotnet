using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// <c>IAIMPConfigFile</c> (apiObjects.h, AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-436F-6E66-6967-46696C650000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPConfigFileNative
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

        [PreserveSig]
        int LoadFromFile(IntPtr fileName);

        [PreserveSig]
        int LoadFromStream(IntPtr stream);

        [PreserveSig]
        int SaveToFile(IntPtr fileName);

        [PreserveSig]
        int SaveToStream(IntPtr stream);
    }
}