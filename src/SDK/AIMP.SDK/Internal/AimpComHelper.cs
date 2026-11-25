using System;
using System.Runtime.InteropServices;

namespace AIMP.Internal
{
    /// <summary>
    /// Low level COM helpers used by the managed bridges.
    /// </summary>
    internal static class AimpComHelper
    {
        /// <summary>
        /// Exposes a managed object that implements a native interface to native
        /// code. The object is pinned so its CCW stays valid.
        /// </summary>
        public static IntPtr GetPointer(object instance, Type interfaceType)
        {
            if (instance == null)
            {
                return IntPtr.Zero;
            }

            var pointer = Marshal.GetComInterfaceForObject(instance, interfaceType);
            AimpRuntime.KeepAlive(instance);
            return pointer;
        }

        /// <summary>
        /// Adds a reference to a raw pointer; the caller owns it.
        /// </summary>
        public static IntPtr AddRef(IntPtr pointer)
        {
            if (pointer == IntPtr.Zero)
            {
                return IntPtr.Zero;
            }

            Marshal.AddRef(pointer);
            return pointer;
        }

        /// <summary>
        /// Queries an interface from a raw pointer; the caller owns it.
        /// </summary>
        public static IntPtr QueryInterface(IntPtr pointer, Guid iid)
        {
            if (pointer == IntPtr.Zero)
            {
                return IntPtr.Zero;
            }

            return Marshal.QueryInterface(pointer, ref iid, out var result) < 0 ? IntPtr.Zero : result;
        }

        /// <summary>
        /// Wraps a native pointer into a typed RCW taking ownership of the reference.
        /// </summary>
        public static T Wrap<T>(IntPtr pointer) where T : class
        {
            if (pointer == IntPtr.Zero)
            {
                return null;
            }

            var instance = (T)Marshal.GetTypedObjectForIUnknown(pointer, typeof(T));

            // The RCW took its own reference, drop the incoming one.
            Marshal.Release(pointer);
            return instance;
        }

        /// <summary>
        /// Reads the <see cref="GuidAttribute"/> of a <c>[ComImport]</c> interface.
        /// </summary>
        public static Guid InterfaceId<T>() where T : class
        {
            var attributes = typeof(T).GetCustomAttributes(typeof(GuidAttribute), false);
            if (attributes.Length == 0)
            {
                throw new InvalidOperationException("Type '" + typeof(T).FullName + "' has no Guid attribute.");
            }

            return new Guid(((GuidAttribute)attributes[0]).Value);
        }

        /// <summary>
        /// Wraps a borrowed pointer, adding a reference.
        /// </summary>
        public static T WrapBorrowed<T>(IntPtr pointer) where T : class
        {
            return pointer == IntPtr.Zero ? null : Wrap<T>(AddRef(pointer));
        }

        public static void Release(IntPtr pointer)
        {
            if (pointer != IntPtr.Zero)
            {
                Marshal.Release(pointer);
            }
        }
    }
}