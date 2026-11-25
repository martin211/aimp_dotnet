using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPExtensionPlaybackQueue2</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7450-6C61-7962636B5132")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionPlaybackQueue2Native
    {
        [PreserveSig]
        int GetNext(IntPtr current, uint flags, IntPtr queueItem);

        [PreserveSig]
        int GetPrev(IntPtr current, uint flags, IntPtr queueItem);

        void OnSelect(IntPtr item, IntPtr queueItem);

        [PreserveSig]
        int GetInfo(IntPtr current, out int position, out int size);
    }
}