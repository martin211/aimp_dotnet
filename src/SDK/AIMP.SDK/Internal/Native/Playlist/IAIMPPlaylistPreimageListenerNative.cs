using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistPreimageListener</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-536D-504C-4D6E-677200000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPPlaylistPreimageListenerNative
    {
        [PreserveSig]
        int DataChanged();

        [PreserveSig]
        int SettingsChanged();
    }
}