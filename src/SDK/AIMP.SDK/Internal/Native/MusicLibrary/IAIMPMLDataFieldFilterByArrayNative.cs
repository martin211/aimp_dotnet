using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataFieldFilterByArray</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-466C-6446-6C7441727200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataFieldFilterByArrayNative
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
        int GetData(IntPtr values, out int count);

        [PreserveSig]
        int SetData(IntPtr values, int count);
    }
}