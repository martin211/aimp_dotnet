using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Plugin
{
    /// <summary>
    /// Native projection of <c>IAIMPExternalSettingsDialog</c> (apiPlugin.h).
    /// AIMP queries the plugin object for this interface to decide whether it
    /// can show an external settings dialog.
    /// </summary>
    [ComVisible(true)]
    [Guid("41494D50-4578-7472-6E4F-7074446C6700")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPExternalSettingsDialogNative
    {
        void Show(IntPtr parentWindow);
    }
}