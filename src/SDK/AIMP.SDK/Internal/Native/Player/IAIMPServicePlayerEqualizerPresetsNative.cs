using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPServicePlayerEqualizerPresets</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7645-5150-727374733200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServicePlayerEqualizerPresetsNative
    {
        [PreserveSig]
        int Add(IntPtr name, in Guid iid, out IntPtr value);

        [PreserveSig]
        int FindByName(IntPtr name, in Guid iid, out IntPtr value);

        [PreserveSig]
        int Delete(IntPtr preset);

        [PreserveSig]
        int Delete2(int index);

        [PreserveSig]
        int GetPreset(int index, in Guid iid, out IntPtr value);

        [PreserveSig]
        int GetPresetCount();
    }
}