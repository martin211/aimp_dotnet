using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// <c>IAIMPHashCode</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-4861-7368-436F-646500000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPHashCodeNative
    {
        [PreserveSig]
        int GetHashCode();

        [PreserveSig]
        void Recalculate();
    }
}