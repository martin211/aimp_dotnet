using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistQueueListener</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-506C-7351-7565-75654C737400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPPlaylistQueueListenerNative
    {
        [PreserveSig]
        void ContentChanged();

        [PreserveSig]
        void StateChanged();
    }
}