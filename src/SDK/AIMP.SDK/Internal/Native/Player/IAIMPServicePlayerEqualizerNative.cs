using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPServicePlayerEqualizer</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7645-5132-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServicePlayerEqualizerNative
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
        int GetActive();

        [PreserveSig]
        int SetActive(int value);

        [PreserveSig]
        int GetPreamp(out double value);

        [PreserveSig]
        int SetPreamp(double value);

        [PreserveSig]
        int GetPreset(in Guid iid, out IntPtr value);

        [PreserveSig]
        int SetPreset(IntPtr value);
    }
}