using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPExtensionFileFormat</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7446-696C-65466D740000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionFileFormatNative
    {
        [PreserveSig]
        int GetDescription(out IntPtr text);

        [PreserveSig]
        int GetExtList(out IntPtr text);

        [PreserveSig]
        int GetFlags(out uint flags);
    }
}