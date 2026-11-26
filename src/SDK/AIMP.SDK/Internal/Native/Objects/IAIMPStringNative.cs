using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// Native projection of <c>IAIMPString</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5374-7269-6E67-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPStringNative
    {
        [PreserveSig]
        int Get(int index, out ushort character);

        [PreserveSig]
        IntPtr GetData();

        [PreserveSig]
        int GetLength();

        [PreserveSig]
        int GetHashCodeNative();

        [PreserveSig]
        int Set(int index, ushort character);

        [PreserveSig]
        int SetData([MarshalAs(UnmanagedType.LPWStr)] string data, int dataLength);

        [PreserveSig]
        int Add(IntPtr source);

        [PreserveSig]
        int Add2([MarshalAs(UnmanagedType.LPWStr)] string chars, int charsCount);

        [PreserveSig]
        int ChangeCase(int mode);

        [PreserveSig]
        int Clone(out IntPtr clone);

        [PreserveSig]
        int Compare(IntPtr source, out int compareResult, int ignoreCase);

        [PreserveSig]
        int Compare2([MarshalAs(UnmanagedType.LPWStr)] string chars, int charsCount, out int compareResult,
            int ignoreCase);

        [PreserveSig]
        int Delete(int index, int count);

        [PreserveSig]
        int Find(IntPtr source, out int index, int flags, int startFromIndex);

        [PreserveSig]
        int Find2([MarshalAs(UnmanagedType.LPWStr)] string chars, int charsCount, out int index, int flags,
            int startFromIndex);

        [PreserveSig]
        int Insert(int index, IntPtr source);

        [PreserveSig]
        int Insert2(int index, [MarshalAs(UnmanagedType.LPWStr)] string chars, int charsCount);

        [PreserveSig]
        int Replace(IntPtr oldPattern, IntPtr newPattern, int flags);

        [PreserveSig]
        int Replace2([MarshalAs(UnmanagedType.LPWStr)] string oldPatternChars, int oldPatternCharsCount,
            [MarshalAs(UnmanagedType.LPWStr)] string newPatternChars, int newPatternCharsCount, int flags);

        [PreserveSig]
        int SubString(int index, int count, out IntPtr substring);
    }
}