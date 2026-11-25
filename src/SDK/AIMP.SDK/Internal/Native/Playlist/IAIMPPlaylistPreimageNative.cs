using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Playlist
{
    /// <summary>
    /// <c>IAIMPPlaylistPreimage</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-536D-504C-5372-630000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPPlaylistPreimageNative
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
        void PreimageFinalize();

        [PreserveSig]
        void Initialize(IntPtr listener);

        [PreserveSig]
        int ConfigLoad(IntPtr stream);

        [PreserveSig]
        int ConfigSave(IntPtr stream);

        [PreserveSig]
        int ExecuteDialog(IntPtr ownerHandle);
    }
}