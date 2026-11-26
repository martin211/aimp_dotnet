using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLPlaylistPreimage</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("414D4C53-6D50-6C73-5372-630000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLPlaylistPreimageNative
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

        [PreserveSig]
        int GetFilter(out IntPtr filter);

        [PreserveSig]
        int GetStorage(out IntPtr storage);
    }
}