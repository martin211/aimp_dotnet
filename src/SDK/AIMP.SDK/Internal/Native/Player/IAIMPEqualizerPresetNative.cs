using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPEqualizerPreset</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4571-5072-7374-320000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPEqualizerPresetNative
    {
        [PreserveSig]
        int GetBandCount();

        [PreserveSig]
        int GetBandFrequency(int bandIndex, out double value);

        [PreserveSig]
        int GetBandGain(int bandIndex, out double value);

        [PreserveSig]
        int SetBandGain(int bandIndex, double value);

        [PreserveSig]
        int GetName(out IntPtr value);

        [PreserveSig]
        int SetName(IntPtr value);
    }
}