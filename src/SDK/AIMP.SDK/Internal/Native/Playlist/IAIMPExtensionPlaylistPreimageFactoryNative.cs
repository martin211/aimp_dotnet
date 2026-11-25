using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPExtensionPlaylistPreimageFactory</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7453-6D50-6C7346637400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionPlaylistPreimageFactoryNative
    {
        [PreserveSig]
        int CreatePreimage(out IntPtr preimage);

        [PreserveSig]
        int GetID(out IntPtr id);

        [PreserveSig]
        int GetName(out IntPtr name);

        [PreserveSig]
        uint GetFlags();
    }
}