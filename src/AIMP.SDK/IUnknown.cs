namespace AIMP.SDK
{
    using System;
    using System.Runtime.InteropServices;

    [ComVisible(false)]
    [ComImport, InterfaceType(ComInterfaceType.InterfaceIsIUnknown), Guid("00000000-0000-0000-C000-000000000046")]
    public interface IUnknownImplementation
    {
        IntPtr QueryInterface(ref Guid riid);

        [PreserveSig]
        UInt32 AddRef();

        [PreserveSig]
        UInt32 Release();
    }
}