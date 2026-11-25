using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLGroupingPresets</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4772-5072-737473000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLGroupingPresetsNative
    {
        [PreserveSig]
        int BeginUpdate();

        [PreserveSig]
        int EndUpdate();

        [PreserveSig]
        int Add(IntPtr id, IntPtr name, uint reserved, IntPtr provider, out IntPtr preset);

        [PreserveSig]
        int Add2(IntPtr id, IntPtr name, uint reserved, IntPtr fieldNames, out IntPtr preset);

        [PreserveSig]
        int Add3(IntPtr id, IntPtr name, uint reserved, IntPtr fieldName, out IntPtr preset);

        [PreserveSig]
        int Delete(int index);

        [PreserveSig]
        int Get(int index, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetByID(IntPtr id, ref Guid iid, out IntPtr obj);

        [PreserveSig]
        int GetCount();
    }
}