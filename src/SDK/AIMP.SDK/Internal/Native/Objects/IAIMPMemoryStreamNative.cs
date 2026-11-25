using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// Native projection of <c>IAIMPMemoryStream</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D65-6D53-7472-65616D000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMemoryStreamNative
    {
        [PreserveSig]
        long GetSize();

        [PreserveSig]
        int SetSize(long value);

        [PreserveSig]
        long GetPosition();

        [PreserveSig]
        int Seek(long offset, int mode);

        [PreserveSig]
        int Read(IntPtr buffer, int count);

        [PreserveSig]
        int Write(IntPtr buffer, int count, out int written);

        [PreserveSig]
        IntPtr GetData();
    }
}