using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Types;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileInfoFormatterUtils</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-6C49-6E66466D7455")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileInfoFormatterUtilsNative
    {
        [PreserveSig]
        int ShowMacrosLegend(AimpNativeRect screenTarget, int reserved, IntPtr eventsHandler);
    }
}