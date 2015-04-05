using System;
using System.Runtime.InteropServices;

namespace AIMP.SDK.Infrastructure.Interfaces
{
    [ComVisible(false)]
    [ComImport,
    InterfaceType(ComInterfaceType.InterfaceIsIUnknown),
    Guid("00000000-0000-0000-C000-000000000046")]
    public interface IUnknown
    {
        IntPtr QueryInterface(ref Guid riid);

        [PreserveSig]
        UInt32 AddRef();

        [PreserveSig]
        UInt32 Release();
    }
}