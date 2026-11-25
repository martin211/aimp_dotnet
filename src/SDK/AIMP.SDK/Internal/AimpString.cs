using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;

namespace AIMP.Internal
{
    /// <summary>
    /// Owning wrapper around a native <c>IAIMPString</c>.
    /// Disposing releases the native reference.
    /// </summary>
    internal sealed class AimpString : IDisposable
    {
        private IAIMPStringNative _native;

        internal AimpString(IntPtr ownedReference, string value)
        {
            _native = (IAIMPStringNative)Marshal.GetTypedObjectForIUnknown(
                ownedReference, typeof(IAIMPStringNative));

            // The RCW took its own reference, drop the incoming one.
            Marshal.Release(ownedReference);

            if (value != null)
            {
                Value = value;
            }
        }

        public string Value
        {
            get
            {
                var native = _native;
                return native == null ? null : ReadValue(native);
            }
            set
            {
                var native = _native;
                if (native == null)
                {
                    throw new ObjectDisposedException(nameof(AimpString));
                }

                var text = value ?? string.Empty;
                var hr = native.SetData(text, text.Length);
                if (hr < 0)
                {
                    throw Marshal.GetExceptionForHR(hr);
                }
            }
        }

        public int Length => _native?.GetLength() ?? 0;

        /// <summary>
        /// Native RCW behind this string.
        /// </summary>
        internal IAIMPStringNative Native => _native;

        /// <summary>
        /// Creates an <c>IAIMPString</c> and returns a raw pointer owned by the
        /// caller (typically native code that stores the object).
        /// </summary>
        public static IntPtr CreateNative(string value)
        {
            var core = AimpRuntime.RequireCore();
            var instance = core.CreateObject(AimpIids.IAIMPString);

            using (var created = new AimpString(instance, value))
            {
                return created.AddRefPointer();
            }
        }

        /// <summary>
        /// Returns a raw pointer to this string; the caller owns the reference.
        /// </summary>
        public IntPtr AddRefPointer()
        {
            var native = _native;
            if (native == null)
            {
                return IntPtr.Zero;
            }

            var unknown = Marshal.GetIUnknownForObject(native);
            try
            {
                var iid = AimpIids.IAIMPString;
                return Marshal.QueryInterface(unknown, ref iid, out var pointer) < 0
                    ? IntPtr.Zero
                    : pointer;
            }
            finally
            {
                Marshal.Release(unknown);
            }
        }

        /// <summary>
        /// Reads a borrowed <c>IAIMPString*</c>. The passed reference is not
        /// consumed.
        /// </summary>
        public static string Read(IntPtr pointer)
        {
            if (pointer == IntPtr.Zero)
            {
                return null;
            }

            var native = (IAIMPStringNative)Marshal.GetObjectForIUnknown(pointer);
            try
            {
                return ReadValue(native);
            }
            finally
            {
                Marshal.ReleaseComObject(native);
            }
        }

        /// <summary>
        /// Reads a native <c>IAIMPString*</c> and consumes the passed reference.
        /// </summary>
        internal static string ReadAndRelease(IntPtr pointer)
        {
            if (pointer == IntPtr.Zero)
            {
                return null;
            }

            try
            {
                var native = (IAIMPStringNative)Marshal.GetTypedObjectForIUnknown(
                    pointer, typeof(IAIMPStringNative));

                try
                {
                    return ReadValue(native);
                }
                finally
                {
                    Marshal.ReleaseComObject(native);
                }
            }
            finally
            {
                Marshal.Release(pointer);
            }
        }

        private static string ReadValue(IAIMPStringNative native)
        {
            var length = native.GetLength();
            if (length <= 0)
            {
                return string.Empty;
            }

            var data = native.GetData();
            return data == IntPtr.Zero ? string.Empty : Marshal.PtrToStringUni(data, length);
        }

        public void Dispose()
        {
            var native = _native;
            _native = null;

            if (native != null)
            {
                Marshal.FinalReleaseComObject(native);
            }
        }
    }
}