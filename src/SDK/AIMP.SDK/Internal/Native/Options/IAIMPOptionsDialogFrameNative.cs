using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Options
{
    /// <summary>
    /// <c>IAIMPOptionsDialogFrame</c> (apiOptions.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4F70-7444-6C67-4672616D6500")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPOptionsDialogFrameNative
    {
        [PreserveSig]
        int GetName(out IntPtr value);

        [PreserveSig]
        IntPtr CreateFrame(IntPtr parentWindow);

        [PreserveSig]
        void DestroyFrame();

        [PreserveSig]
        void Notification(int id);
    }
}