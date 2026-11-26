using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLGroupingTreeDataProvider2</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4772-7044-617461507232")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPMLGroupingTreeDataProvider2Native
    {
        [PreserveSig]
        int AppendFilter(IntPtr filter, IntPtr selection);

        [PreserveSig]
        uint GetCapabilities();

        [PreserveSig]
        int GetData(IntPtr selection, out IntPtr data);

        [PreserveSig]
        int GetFieldForAlphabeticIndex(out IntPtr fieldName);

        [PreserveSig]
        ushort GetPathSeparator();
    }
}