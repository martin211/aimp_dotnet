using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLSortDirection</c> (apiMusicLibrary.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-536F-7274-446972746E00")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPMLSortDirectionNative
    {
        [PreserveSig]
        int GetValue(out int value);

        [PreserveSig]
        int SetValue(int value);
    }
}