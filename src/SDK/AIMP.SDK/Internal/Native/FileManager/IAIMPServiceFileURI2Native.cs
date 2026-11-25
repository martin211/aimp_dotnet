using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.FileManager
{
    /// <summary>
    /// <c>IAIMPServiceFileURI2</c> (apiFileManager.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7646-696C-655552493200")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileURI2Native
    {
        [PreserveSig]
        int Build(IntPtr containerFileName, IntPtr partName, out IntPtr fileUri);

        [PreserveSig]
        int Parse(IntPtr fileUri, out IntPtr containerFileName, out IntPtr partName);

        [PreserveSig]
        int ChangeFileExt(ref IntPtr fileUri, IntPtr newExt, uint flags);

        [PreserveSig]
        int ExtractFileExt(IntPtr fileUri, out IntPtr value, uint flags);

        [PreserveSig]
        int ExtractFileName(IntPtr fileUri, out IntPtr value);

        [PreserveSig]
        int ExtractFileParentDirName(IntPtr fileUri, out IntPtr value);

        [PreserveSig]
        int ExtractFileParentName(IntPtr fileUri, out IntPtr value);

        [PreserveSig]
        int ExtractFilePath(IntPtr fileUri, out IntPtr value);

        [PreserveSig]
        int IsURL(IntPtr fileUri);

        [PreserveSig]
        int GetScheme(IntPtr fileUri, out IntPtr scheme);
    }
}