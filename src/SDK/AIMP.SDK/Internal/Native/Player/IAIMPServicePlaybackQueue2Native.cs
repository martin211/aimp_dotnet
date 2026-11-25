using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPServicePlaybackQueue2</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7650-6C62-61636B513200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServicePlaybackQueue2Native
    {
        [PreserveSig]
        int GetNextTrack(out IntPtr item);

        [PreserveSig]
        int GetPrevTrack(out IntPtr item);

        [PreserveSig]
        int NotifyChanged(IntPtr sender);
    }
}