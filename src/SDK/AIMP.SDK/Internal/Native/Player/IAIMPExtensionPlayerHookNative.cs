using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Player
{
    /// <summary>
    /// <c>IAIMPExtensionPlayerHook</c> (apiPlayer.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4578-7450-6C72-486F6F6B0000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPExtensionPlayerHookNative
    {
        [PreserveSig]
        int OnCheckURL(IntPtr url, out int handled);
    }
}