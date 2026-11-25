using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;

namespace AIMP.Internal
{
    /// <summary>
    /// Wrapper around a native <c>IAIMPObjectList</c>.
    /// </summary>
    internal sealed class AimpObjectList : IDisposable
    {
        private readonly IAIMPObjectListNative _native;

        public AimpObjectList(IntPtr pointer)
        {
            Pointer = pointer;
            _native = AimpComHelper.Wrap<IAIMPObjectListNative>(pointer);
        }

        /// <summary>
        /// Native <c>IUnknown*</c> of the list; valid until disposed.
        /// </summary>
        public IntPtr Pointer { get; }

        /// <summary>
        /// Creates an empty object list.
        /// </summary>
        public static AimpObjectList Create()
        {
            return new AimpObjectList(
                AimpRuntime.RequireCore().CreateObject(AimpIids.IAIMPObjectList));
        }

        public int Count => _native.GetCount();

        /// <summary>
        /// Returns an owned <c>IUnknown*</c> of the list.
        /// </summary>
        public IntPtr AddRefPointer()
        {
            return Marshal.GetIUnknownForObject(_native);
        }

        /// <summary>
        /// Returns an owned <c>IAIMPObjectList*</c> of the list.
        /// </summary>
        public IntPtr AddRefInterfacePointer()
        {
            var unknown = Marshal.GetIUnknownForObject(_native);
            try
            {
                var iid = AimpIids.IAIMPObjectList;
                return Marshal.QueryInterface(unknown, ref iid, out var pointer) < 0
                    ? IntPtr.Zero
                    : pointer;
            }
            finally
            {
                Marshal.Release(unknown);
            }
        }

        public void Add(IntPtr instance)
        {
            _native.Add(instance);
        }

        public void Add(string value)
        {
            var pointer = AimpString.CreateNative(value);
            try
            {
                var hr = _native.Add(pointer);
                if (hr < 0)
                {
                    AimpLog.Write(
                        $"IAIMPObjectList.Add(string) failed: hr=0x{hr.ToString("X8")}, value='{value}'.");
                }
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public void Add(object instance, Type interfaceType)
        {
            var pointer = AimpComHelper.GetPointer(instance, interfaceType);
            _native.Add(pointer);
        }

        /// <summary>
        /// Adds a managed/native COM object by its <c>IUnknown</c> pointer.
        /// </summary>
        public void AddUnknown(object instance)
        {
            if (instance == null)
            {
                return;
            }

            var pointer = Marshal.GetIUnknownForObject(instance);
            try
            {
                _native.Add(pointer);
            }
            finally
            {
                Marshal.Release(pointer);
            }
        }

        /// <summary>
        /// Reads an item as a string, or <c>null</c> when it is not an <c>IAIMPString</c>.
        /// </summary>
        public string GetString(int index)
        {
            var pointer = GetObject(index, AimpIids.IAIMPString);
            return pointer == IntPtr.Zero ? null : AimpString.ReadAndRelease(pointer);
        }

        /// <summary>
        /// Returns an owned pointer to the item.
        /// </summary>
        public IntPtr GetObject(int index, Guid iid)
        {
            return _native.GetObject(index, ref iid, out var pointer) < 0 ? IntPtr.Zero : pointer;
        }

        public IEnumerable<string> AsStrings()
        {
            var count = Count;
            for (var i = 0; i < count; i++)
            {
                yield return GetString(i);
            }
        }

        public void Dispose()
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}