using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPEqualizerBands</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4571-4261-6E64-730000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPEqualizerBandsNative
    {
        [PreserveSig]
        int GetBandCount();

        [PreserveSig]
        int GetBandFrequency(int bandIndex, out double value);

        [PreserveSig]
        int GetBandGain(int bandIndex, out double value);

        [PreserveSig]
        int SetBandGain(int bandIndex, double value);
    }
}