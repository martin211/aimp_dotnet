using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPServicePlayer2</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7650-6C61-796572320000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServicePlayer2Native
    {
        [PreserveSig]
        int Play(IntPtr item);

        [PreserveSig]
        int Play2(IntPtr item);

        [PreserveSig]
        int Play3(IntPtr playlist);

        [PreserveSig]
        int Play4(IntPtr fileUri, uint flags);

        [PreserveSig]
        int GoToNext();

        [PreserveSig]
        int GoToPrev();

        [PreserveSig]
        int GetDuration(out double seconds);

        [PreserveSig]
        int GetPosition(out double seconds);

        [PreserveSig]
        int SetPosition(double seconds);

        [PreserveSig]
        int GetMute(out int value);

        [PreserveSig]
        int SetMute(int value);

        [PreserveSig]
        int GetVolume(out float level);

        [PreserveSig]
        int SetVolume(float level);

        [PreserveSig]
        int GetInfo(out IntPtr fileInfo);

        [PreserveSig]
        int GetPlaylistItem(out IntPtr item);

        [PreserveSig]
        int GetState();

        [PreserveSig]
        int Pause();

        [PreserveSig]
        int Resume();

        [PreserveSig]
        int Stop();

        [PreserveSig]
        int StopAfterTrack();

        [PreserveSig]
        int PlayWithOffset(IntPtr item, float offset, uint flags);

        [PreserveSig]
        int Play2WithOffset(IntPtr item, float offset, uint flags);

        [PreserveSig]
        int Play4WithOffset(IntPtr fileUri, float offset, uint flags);
    }
}