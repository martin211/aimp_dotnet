using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLGroupingTreeDataProviderSelection</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4772-4474-50727653656C")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPMLGroupingTreeDataProviderSelectionNative
    {
        [PreserveSig]
        int GetDisplayValue(out IntPtr value);

        [PreserveSig]
        uint GetFlags();

        [PreserveSig]
        int GetImageIndex(out int index);

        [PreserveSig]
        int GetValue(out IntPtr fieldName, IntPtr value);

        [PreserveSig]
        int NextRecord();
    }
}