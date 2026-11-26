using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MessageDispatcher
{
    /// <summary>
    /// <c>IAIMPMessageHook</c> (apiMessages.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("FC6FB524-A959-4089-AA0A-EA40AB7374CD")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAIMPMessageHookNative
    {
        [PreserveSig]
        void CoreMessage(uint message, int param1, IntPtr param2, IntPtr result);
    }
}