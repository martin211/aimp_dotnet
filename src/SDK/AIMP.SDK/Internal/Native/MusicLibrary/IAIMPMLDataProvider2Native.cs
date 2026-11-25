using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataProvider2</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4461-7461-507276320000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataProvider2Native
    {
        [PreserveSig]
        int GetData(IntPtr fields, IntPtr filter, IntPtr reserved, ref IntPtr pageId, out IntPtr data);
    }
}