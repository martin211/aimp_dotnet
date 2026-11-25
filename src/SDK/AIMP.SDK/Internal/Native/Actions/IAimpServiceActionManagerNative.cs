using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Actions
{
    /// <summary>
    /// <c>IAIMPServiceActionManager</c>.
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5372-7641-6374-696F6E4D616E")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAimpServiceActionManagerNative
    {
        [PreserveSig]
        int GetByID(IntPtr id, out IntPtr action);

        [PreserveSig]
        int MakeHotkey(ushort modifiers, ushort key);
    }
}