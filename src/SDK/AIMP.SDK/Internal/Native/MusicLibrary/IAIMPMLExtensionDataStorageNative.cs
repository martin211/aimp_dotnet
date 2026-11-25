using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLExtensionDataStorage</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-744D-4C44-530000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPMLExtensionDataStorageNative
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
        void StorageFinalize();

        [PreserveSig]
        void Initialize(IntPtr manager);

        [PreserveSig]
        int ConfigLoad(IntPtr config, IntPtr section);

        [PreserveSig]
        int ConfigSave(IntPtr config, IntPtr section);

        [PreserveSig]
        int GetFields(int schema, out IntPtr list);

        [PreserveSig]
        int GetGroupingPresets(int schema, IntPtr presets);

        [PreserveSig]
        void FlushCache(int reserved);
    }
}