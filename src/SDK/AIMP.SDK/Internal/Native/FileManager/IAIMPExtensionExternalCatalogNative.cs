using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPExtensionExternalCatalog</c> (apiFileManager.h, AIMP 6.0+).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7445-7874-726E43617400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionExternalCatalogNative
    {
        [PreserveSig]
        int GetIcon(out IntPtr image);

        [PreserveSig]
        int GetName(out IntPtr name);

        [PreserveSig]
        int Show(IntPtr ownerWindow, IntPtr data);
    }
}