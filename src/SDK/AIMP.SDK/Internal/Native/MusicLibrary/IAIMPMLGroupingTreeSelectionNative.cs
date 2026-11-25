using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLGroupingTreeSelection</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4770-5472-656553656C00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLGroupingTreeSelectionNative
    {
        [PreserveSig]
        int GetCount();

        [PreserveSig]
        int GetValue(int index, out IntPtr fieldName, IntPtr value);
    }
}