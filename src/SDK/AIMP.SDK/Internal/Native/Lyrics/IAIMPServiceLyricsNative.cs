using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Lyrics
{
    /// <summary>
    /// <c>IAIMPServiceLyrics</c> (apiLyrics.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764C-7972-697800000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceLyricsNative
    {
        [PreserveSig]
        int Get(IntPtr fileInfo, uint flags, IntPtr callback, IntPtr userData, out IntPtr taskId);

        [PreserveSig]
        int Cancel(IntPtr taskId, uint flags);
    }
}