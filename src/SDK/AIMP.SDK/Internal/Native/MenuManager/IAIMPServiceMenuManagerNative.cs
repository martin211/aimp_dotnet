using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MenuManager
{
    /// <summary>
    /// <c>IAIMPServiceMenuManager</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764D-656E-754D6E677200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceMenuManagerNative
    {
        [PreserveSig]
        int GetBuiltIn(int id, out IntPtr menuItem);

        [PreserveSig]
        int GetByID(IntPtr id, out IntPtr menuItem);
    }
}