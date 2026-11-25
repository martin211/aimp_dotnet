using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataFieldDisplayValue</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4461-7461-466C6444566C")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataFieldDisplayValueNative
    {
        [PreserveSig]
        IntPtr GetDisplayValue(IntPtr value, out int length);
    }
}