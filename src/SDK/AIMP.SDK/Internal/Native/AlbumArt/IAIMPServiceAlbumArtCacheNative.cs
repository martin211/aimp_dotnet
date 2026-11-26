using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.AlbumArt
{
    /// <summary>
    /// <c>IAIMPServiceAlbumArtCache</c> (apiAlbumArt.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7641-6C62-417274434300")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceAlbumArtCacheNative
    {
        [PreserveSig]
        int Flush();

        [PreserveSig]
        int Get(IntPtr key, out IntPtr imageContainer);

        [PreserveSig]
        int Put(IntPtr key, ref IntPtr imageContainer);

        [PreserveSig]
        int Remove(IntPtr key);

        [PreserveSig]
        int Stat(out long size, out uint count);
    }
}