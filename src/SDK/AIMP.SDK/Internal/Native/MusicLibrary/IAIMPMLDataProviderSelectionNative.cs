using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataProviderSelection</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4461-7461-50727653656C")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPMLDataProviderSelectionNative
    {
        [PreserveSig]
        double GetValueAsFloat(int fieldIndex);

        [PreserveSig]
        int GetValueAsInt32(int fieldIndex);

        [PreserveSig]
        long GetValueAsInt64(int fieldIndex);

        [PreserveSig]
        IntPtr GetValueAsString(int fieldIndex, out int length);

        [PreserveSig]
        int NextRow();
    }
}