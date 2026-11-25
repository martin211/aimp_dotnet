using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// Native projection of <c>IAIMPStream</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5374-7265-616D-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPStreamNative
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
    }
}