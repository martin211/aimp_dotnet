using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Options
{
    /// <summary>
    /// <c>IAIMPOptionsDialogFrameKeyboardHelper</c> (apiOptions.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4F70-7444-6C67-46726D4B4870")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPOptionsDialogFrameKeyboardHelperNative
    {
        [PreserveSig]
        int DialogKey(ushort charCode, int unused);

        [PreserveSig]
        int SelectFirstControl();

        [PreserveSig]
        int SelectNextControl(int findForward, int checkTabStop);
    }
}