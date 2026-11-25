using System.Runtime.InteropServices;

namespace AIMP.Internal.Native.Types
{
    [StructLayout(LayoutKind.Sequential)]
    public struct AimpNativeRect
    {
        public int Left;
        public int Top;
        public int Right;
        public int Bottom;
    }
}