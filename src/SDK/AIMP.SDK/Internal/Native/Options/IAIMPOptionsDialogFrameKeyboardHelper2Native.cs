using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Options
{
    /// <summary>
    /// <c>IAIMPOptionsDialogFrameKeyboardHelper2</c> (apiOptions.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4F70-7444-6C67-46726D4B4832")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPOptionsDialogFrameKeyboardHelper2Native
    {
        [PreserveSig]
        int DialogKey(ushort charCode, int unused);

        [PreserveSig]
        int SelectFirstControl();

        [PreserveSig]
        int SelectNextControl(int findForward, int checkTabStop);

        [PreserveSig]
        int SelectLastControl();
    }
}