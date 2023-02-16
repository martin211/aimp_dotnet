//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Runtime.InteropServices;

namespace AIMP.SDK.MessageDispatcher
{
    public static class PointerExtension
    {
        public static byte ToByte(this IntPtr pointer)
        {
            return Marshal.ReadByte(pointer);
        }

        public static bool ToBool(this IntPtr pointer)
        {
            return Convert.ToBoolean(ToByte(pointer));
        }

        public static int ToInt(this IntPtr pointer)
        {
            byte[] ba = new byte[sizeof(int)];

            for (int i = 0; i < ba.Length; i++)
            {
                ba[i] = Marshal.ReadByte(pointer, i);
            }
            int v = BitConverter.ToInt32(ba, 0);
            return v;
        }

        public static double ToDouble(this IntPtr pointer)
        {
            byte[] ba = new byte[sizeof(double)];

            for (int i = 0; i < ba.Length; i++)
            {
                ba[i] = Marshal.ReadByte(pointer, i);
            }
            double v = BitConverter.ToDouble(ba, 0);
            return v;
        }

        public static IntPtr ToPointer(this bool value)
        {
            int size = Marshal.SizeOf(typeof(int));
            IntPtr pointer = Marshal.AllocHGlobal(size);
            Marshal.WriteInt32(pointer, 0, value ? 1 : 0);
            return pointer;
        }

        public static IntPtr ToPointer(this double value)
        {
            var ptr = Marshal.AllocHGlobal(sizeof(double));
            byte[] byteDouble = BitConverter.GetBytes(value);
            Marshal.Copy(byteDouble, 0, ptr, byteDouble.Length);
            return ptr;
        }

        public static IntPtr ToPointer(this int value)
        {
            int size = Marshal.SizeOf(typeof(int));
            IntPtr pointer = Marshal.AllocHGlobal(size);
            Marshal.WriteInt32(pointer, 0, value);
            return pointer;
        }

        public static IntPtr ToPointer(this object value)
        {
            if (value is bool boolVal)
            {
                return ToPointer(boolVal);
            }

            if (value is double doubleVal)
            {
                return ToPointer(doubleVal);
            }

            if (value is int intVal)
            {
                return ToPointer(intVal);
            }

            return IntPtr.Zero;
        }
    }
}
