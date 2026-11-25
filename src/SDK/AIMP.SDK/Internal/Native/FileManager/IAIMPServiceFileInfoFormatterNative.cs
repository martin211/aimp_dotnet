using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileInfoFormatter</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-6C49-6E66466D7400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileInfoFormatterNative
    {
        [PreserveSig]
        int Format(IntPtr template, IntPtr fileInfo, int reserved, IntPtr additionalInfo, out IntPtr formattedResult);
    }
}