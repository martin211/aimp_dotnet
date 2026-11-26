using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPExtensionWaveformProvider</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7457-6176-507276000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionWaveformProviderNative
    {
        [PreserveSig]
        int Calculate(IntPtr fileUri, IntPtr taskOwner, IntPtr peaks, int peakCount);
    }
}