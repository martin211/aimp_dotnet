using System;
using System.Runtime.InteropServices;

namespace AIMP.SDK
{
    [Serializable]
    [StructLayout(LayoutKind.Explicit)]
    public struct Variant
    {
        [FieldOffset(0)]
        public int Integer;

        [FieldOffset(0)]
        public float Float;

        [FieldOffset(0)]
        public double Double;

        [FieldOffset(0)]
        public byte Byte;

        [FieldOffset(0)]
        public string String;
    }
}
