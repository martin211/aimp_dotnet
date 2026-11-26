using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLGroupingTreeDataProvider</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4772-7044-617461507276")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLGroupingTreeDataProviderNative
    {
        [PreserveSig]
        int AppendFilter(IntPtr filter, IntPtr selection);

        [PreserveSig]
        uint GetCapabilities();

        [PreserveSig]
        int GetData(IntPtr selection, out IntPtr data);

        [PreserveSig]
        int GetFieldForAlphabeticIndex(out IntPtr fieldName);
    }
}