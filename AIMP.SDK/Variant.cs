using System;
using System.Diagnostics.Contracts;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Runtime.Versioning;

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
    }
}
