using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLFileList</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4669-6C65-4C6973740000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLFileListNative
    {
        [PreserveSig]
        int Add(IntPtr id, IntPtr fileName);

        [PreserveSig]
        int Clear();

        [PreserveSig]
        int Delete(int index);

        [PreserveSig]
        int Insert(int index, IntPtr id, IntPtr fileName);

        [PreserveSig]
        int GetCount();

        [PreserveSig]
        int GetFileName(int index, out IntPtr fileName);

        [PreserveSig]
        int SetFileName(int index, IntPtr fileName);

        [PreserveSig]
        int GetID(int index, out IntPtr id);

        [PreserveSig]
        int SetID(int index, IntPtr id);

        [PreserveSig]
        int Clone(out IntPtr obj);
    }
}