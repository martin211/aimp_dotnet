using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// Native projection of <c>IAIMPObjectList2</c> (apiObjects.h, AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4F62-6A4C-6973-743200000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPObjectList2Native
    {
        [PreserveSig]
        int Add(IntPtr obj);

        [PreserveSig]
        int Clear();

        [PreserveSig]
        int Delete(int index);

        [PreserveSig]
        int Insert(int index, IntPtr obj);

        [PreserveSig]
        int GetCount();

        [PreserveSig]
        int GetObject(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int SetObject(int index, IntPtr obj);

        [PreserveSig]
        int IndexOf(IntPtr obj);
    }
}