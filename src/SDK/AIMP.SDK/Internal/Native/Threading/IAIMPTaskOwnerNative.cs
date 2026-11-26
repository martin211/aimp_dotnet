using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Threading
{
    /// <summary>
    /// <c>IAIMPTaskOwner</c> (apiThreading.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-5461-736B-4F77-6E6572320000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPTaskOwnerNative
    {
        [PreserveSig]
        int IsCanceled();
    }
}