using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.AlbumArt
{
    /// <summary>
    /// <c>IAIMPServiceAlbumArt</c> (apiAlbumArt.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7641-6C62-417274000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceAlbumArtNative
    {
        [PreserveSig]
        int Get(IntPtr fileUri, IntPtr artist, IntPtr album, uint flags, IntPtr callback, IntPtr userData, out IntPtr taskId);

        [PreserveSig]
        int Get2(IntPtr fileInfo, uint flags, IntPtr callback, IntPtr userData, out IntPtr taskId);

        [PreserveSig]
        int Cancel(IntPtr taskId, uint flags);
    }
}