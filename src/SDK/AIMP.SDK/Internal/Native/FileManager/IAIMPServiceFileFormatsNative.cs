using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileFormats</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-696C-65466D747300")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileFormatsNative
    {
        [PreserveSig]
        int GetFormats(uint flags, out IntPtr formats);

        [PreserveSig]
        int IsSupported(IntPtr fileName, uint flags);
    }
}