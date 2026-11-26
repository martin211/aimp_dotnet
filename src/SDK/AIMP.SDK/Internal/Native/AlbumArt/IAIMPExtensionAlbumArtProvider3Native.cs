using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.AlbumArt
{
    /// <summary>
    /// <c>IAIMPExtensionAlbumArtProvider3</c> (apiAlbumArt.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-416C-6241-727450727633")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionAlbumArtProvider3Native
    {
        [PreserveSig]
        int Get(IntPtr fileInfo, IntPtr request, out IntPtr image);

        [PreserveSig]
        uint GetCategory();
    }
}