using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Types;

namespace AIMP.Internal.Native.Objects
{
    /// <summary>
    /// <c>IAIMPImage</c> (apiObjects.h).
    /// </summary>
    [ComImport]
    [ComVisible(true)]
    [Guid("41494D50-496D-6167-6500-000000000000")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IAIMPImageNative
    {
        [PreserveSig]
        int LoadFromFile(IntPtr fileName);

        [PreserveSig]
        int LoadFromStream(IntPtr stream);

        [PreserveSig]
        int SaveToFile(IntPtr fileName, int formatId);

        [PreserveSig]
        int SaveToStream(IntPtr stream, int formatId);

        [PreserveSig]
        int GetFormatID();

        [PreserveSig]
        int GetSize(out AimpNativeSize size);

        [PreserveSig]
        int Clone(out IntPtr image);

        [PreserveSig]
        int Draw(IntPtr canvas, AimpNativeRect rect, uint flags, IntPtr attrs);

        [PreserveSig]
        int Resize(int width, int height);
    }
}