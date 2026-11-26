using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.MessageDispatcher
{
    /// <summary>
    /// <c>IAIMPServiceMessageDispatcher</c> (apiMessages.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-764D-7367-447370720000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPServiceMessageDispatcherNative
    {
        [PreserveSig]
        int Send(uint message, int param1, IntPtr param2);

        [PreserveSig]
        uint Register(IntPtr messageName);

        [PreserveSig]
        int Hook(IntPtr hook);

        [PreserveSig]
        int Unhook(IntPtr hook);
    }
}