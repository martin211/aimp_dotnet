using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Types
{
    [StructLayout(LayoutKind.Sequential)]
    public struct AimpNativeSize
    {
        public int Width;
        public int Height;
    }
}