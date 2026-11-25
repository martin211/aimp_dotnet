using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MusicLibrary
{
    /// <summary>
    /// <c>IAIMPMLDataStorageCommandReportDialog</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4D4C-4453-436D-645270727400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPMLDataStorageCommandReportDialogNative
    {
        [PreserveSig]
        int Execute(IntPtr ownerHandle);
    }
}