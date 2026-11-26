using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.TagEditor
{
    /// <summary>
    /// <c>IAIMPFileTagEditor</c> (apiTagEditor.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4669-6C65-5461-674564697400")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPFileTagEditorNative
    {
        [PreserveSig]
        int GetMixedInfo(out IntPtr value);

        [PreserveSig]
        int GetTag(int index, in Guid iid, out IntPtr value);

        [PreserveSig]
        int GetTagCount();

        [PreserveSig]
        int SetToAll(IntPtr fileInfo);

        [PreserveSig]
        int Save();
    }
}