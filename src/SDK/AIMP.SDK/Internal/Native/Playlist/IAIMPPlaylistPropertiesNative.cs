using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistProperties</c> (apiPlaylists.h, AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-506C-7350-726F-707300000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPPlaylistPropertiesNative
    {
        [PreserveSig]
        void BeginUpdate();

        [PreserveSig]
        void EndUpdate();

        [PreserveSig]
        int Reset();

        [PreserveSig]
        int GetValueAsFloat(int propertyId, out double value);

        [PreserveSig]
        int GetValueAsInt32(int propertyId, out int value);

        [PreserveSig]
        int GetValueAsInt64(int propertyId, out long value);

        [PreserveSig]
        int GetValueAsObject(int propertyId, ref Guid iid, out IntPtr value);

        [PreserveSig]
        int SetValueAsFloat(int propertyId, double value);

        [PreserveSig]
        int SetValueAsInt32(int propertyId, int value);

        [PreserveSig]
        int SetValueAsInt64(int propertyId, long value);

        [PreserveSig]
        int SetValueAsObject(int propertyId, IntPtr value);

        [PreserveSig]
        int GetValueAsVariant(int propertyId, IntPtr value);

        [PreserveSig]
        int SetValueAsVariant(int propertyId, IntPtr value);

        [PreserveSig]
        int GetCustomValue(IntPtr name, out IntPtr value);

        [PreserveSig]
        int SetCustomValue(IntPtr name, IntPtr value);
    }
}