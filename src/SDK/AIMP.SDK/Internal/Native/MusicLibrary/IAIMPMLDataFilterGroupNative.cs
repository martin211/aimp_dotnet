using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataFilterGroup</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-466C-7447-727000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataFilterGroupNative
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
        int Add(IntPtr field, IntPtr value1, IntPtr value2, int operation, out IntPtr filter);

        [PreserveSig]
        int Add2(IntPtr field, IntPtr values, int count, out IntPtr filter);

        [PreserveSig]
        int AddGroup(out IntPtr group);

        [PreserveSig]
        int Clear();

        [PreserveSig]
        int Delete(int index);

        [PreserveSig]
        int GetChild(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetChildCount();
    }
}