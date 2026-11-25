using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPExtensionPlaybackQueue</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7450-6C61-796261636B51")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionPlaybackQueueNative
    {
        [PreserveSig]
        int GetNext(IntPtr current, uint flags, IntPtr queueItem);

        [PreserveSig]
        int GetPrev(IntPtr current, uint flags, IntPtr queueItem);

        void OnSelect(IntPtr item, IntPtr queueItem);
    }
}