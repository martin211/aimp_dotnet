using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.TagEditor
{
    /// <summary>
    /// <c>IAIMPServiceFileTagEditor</c> (apiTagEditor.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7654-6167-456469740000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceFileTagEditorNative
    {
        [PreserveSig]
        int EditFile(IntPtr source, in Guid iid, out IntPtr value);

        [PreserveSig]
        int EditTag(IntPtr source, int tagId, in Guid iid, out IntPtr value);
    }
}