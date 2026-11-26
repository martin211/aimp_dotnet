using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace AIMP.Internal
{
    /// <summary>
    /// Helpers for the native <c>VARIANT</c> type used by data filters and
    /// grouping tree selections.
    /// </summary>
    internal static class AimpVariant
    {
        [StructLayout(LayoutKind.Sequential)]
        private struct NativeVariant
        {
            public ushort Vt;
            public ushort Reserved1;
            public ushort Reserved2;
            public ushort Reserved3;
            public IntPtr Data1;
            public IntPtr Data2;
        }

        private static readonly int VariantSize = Marshal.SizeOf(typeof(NativeVariant));

        [DllImport("oleaut32.dll", ExactSpelling = true, PreserveSig = true)]
        private static extern int VariantClear(IntPtr variant);

        /// <summary>
        /// Allocates a VARIANT on the native heap. The caller owns the result and
        /// must pass it to <see cref="Free"/>.
        /// </summary>
        public static IntPtr Alloc(object value)
        {
            var pointer = Marshal.AllocHGlobal(VariantSize);

            for (var i = 0; i < VariantSize; i++)
            {
                Marshal.WriteByte(pointer, i, 0);
            }

            if (value != null)
            {
                Marshal.GetNativeVariantForObject(value, pointer);
            }

            return pointer;
        }

        /// <summary>
        /// Size of a native VARIANT in bytes.
        /// </summary>
        public static int Size => VariantSize;

        /// <summary>
        /// Allocates a contiguous array of VARIANTs on the native heap. The
        /// caller owns the result and must pass it to
        /// <see cref="FreeArray(IntPtr, int)"/>.
        /// </summary>
        public static IntPtr AllocArray(IList<object> values, out int count)
        {
            count = values?.Count ?? 0;
            if (count == 0)
            {
                return IntPtr.Zero;
            }

            var pointer = Marshal.AllocHGlobal(VariantSize * count);

            for (var i = 0; i < VariantSize * count; i++)
            {
                Marshal.WriteByte(pointer, i, 0);
            }

            for (var i = 0; i < count; i++)
            {
                var item = values[i];
                if (item != null)
                {
                    Marshal.GetNativeVariantForObject(item, IntPtr.Add(pointer, i * VariantSize));
                }
            }

            return pointer;
        }

        /// <summary>
        /// Reads an array of native VARIANTs.
        /// </summary>
        public static IList<object> ReadArray(IntPtr pointer, int count)
        {
            var result = new List<object>(count);

            for (var i = 0; i < count; i++)
            {
                result.Add(Read(IntPtr.Add(pointer, i * VariantSize)));
            }

            return result;
        }

        /// <summary>
        /// Frees an array allocated by <see cref="AllocArray"/>.
        /// </summary>
        public static void FreeArray(IntPtr pointer, int count)
        {
            if (pointer == IntPtr.Zero)
            {
                return;
            }

            for (var i = 0; i < count; i++)
            {
                VariantClear(IntPtr.Add(pointer, i * VariantSize));
            }

            Marshal.FreeHGlobal(pointer);
        }

        /// <summary>
        /// Reads a VARIANT owned by native code.
        /// </summary>
        public static object Read(IntPtr variant)
        {
            return variant == IntPtr.Zero ? null : Marshal.GetObjectForNativeVariant(variant);
        }

        /// <summary>
        /// Frees a VARIANT allocated by <see cref="Alloc"/>.
        /// </summary>
        public static void Free(IntPtr variant)
        {
            if (variant == IntPtr.Zero)
            {
                return;
            }

            VariantClear(variant);
            Marshal.FreeHGlobal(variant);
        }
    }
}