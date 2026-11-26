using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistListener2</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-506C-734C-7374-6E7232000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPPlaylistListener2Native
    {
        [PreserveSig]
        void ScanningBegin();

        [PreserveSig]
        void ScanningProgress(double progress);

        [PreserveSig]
        void ScanningEnd(int hasChanges, int canceled);
    }
}