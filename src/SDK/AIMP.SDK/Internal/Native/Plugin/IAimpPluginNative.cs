using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Plugin
{
    /// <summary>
    /// Native projection of <c>IAIMPPlugin</c> (apiPlugin.h).
    ///
    /// This one goes in the opposite direction: a managed class implements it
    /// and .NET exposes the implementation to native code as a CCW through
    /// <see cref="Marshal.GetComInterfaceForObject(object, Type)"/>.
    ///
    /// AIMP does not use an IID to obtain IAIMPPlugin (the SDK declares no
    /// IID_IAIMPPlugin), so any valid GUID can be used here.
    /// </summary>
    [ComVisible(true)]
    [Guid("41494D50-506C-7567-696E-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    public interface IAimpPluginNative
    {
        [PreserveSig]
        IntPtr InfoGet(int index);

        [PreserveSig]
        uint InfoGetCategories();

        [PreserveSig]
        int Initialize(IntPtr core);

        [PreserveSig]
        int Finalize();

        [PreserveSig]
        void SystemNotification(int notifyId, IntPtr data);
    }
}