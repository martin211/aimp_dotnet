using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistListener</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-506C-734C-7374-6E7200000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPPlaylistListenerNative
    {
        [PreserveSig]
        void Activated();

        [PreserveSig]
        void Changed(uint flags);

        [PreserveSig]
        void Removed();
    }
}