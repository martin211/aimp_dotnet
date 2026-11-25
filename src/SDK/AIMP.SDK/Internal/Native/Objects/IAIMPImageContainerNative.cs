using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Types;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// <c>IAIMPImageContainer</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-496D-6167-6543-6F6E746E7200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPImageContainerNative
    {
        [PreserveSig]
        int CreateImage(out IntPtr image);

        [PreserveSig]
        int GetInfo(out AimpNativeSize size, out int format);

        [PreserveSig]
        IntPtr GetData();

        [PreserveSig]
        uint GetDataSize();

        [PreserveSig]
        int SetDataSize(uint value);
    }
}