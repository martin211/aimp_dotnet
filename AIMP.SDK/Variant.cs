using System;
using System.Runtime.InteropServices;

namespace AIMP.SDK
{
    [Serializable]
    [StructLayout(LayoutKind.Explicit)]
    public struct Variant
    {
        [FieldOffset(4)]
        public int Integer;

        [FieldOffset(5)]
        public float Float;

        [FieldOffset(6)]
        public double Double;

        [FieldOffset(7)]
        public byte Byte;

        [FieldOffset(8)]
        public string String;
    }
}
