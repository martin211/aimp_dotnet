using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPServiceMusicLibraryUI</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764D-4C55-490000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceMusicLibraryUINative
    {
        [PreserveSig]
        int GetFiles(uint flags, out IntPtr list);

        [PreserveSig]
        int GetGroupingFilter(out IntPtr filter);

        [PreserveSig]
        int GetGroupingFilterPath(out IntPtr path);

        [PreserveSig]
        int SetGroupingFilterPath(IntPtr path);
    }
}