using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;

namespace AIMP.Internal
{
    /// <summary>
    /// Typed access to any native object that exposes
    /// <c>IAIMPPropertyList</c> (<c>IAIMPPropertyList2</c>).
    /// </summary>
    internal sealed class AimpPropertyBag : IDisposable
    {
        private readonly IAIMPPropertyListNative _properties;
        private readonly bool _owns;
        private IAIMPPropertyList2Native _properties2;

        /// <summary>
        /// Wraps a borrowed property list pointer; the bag owns its reference.
        /// </summary>
        public AimpPropertyBag(IntPtr pointer)
            : this(AimpComHelper.WrapBorrowed<IAIMPPropertyListNative>(pointer), true)
        {
        }

        /// <summary>
        /// Wraps a pointer whose reference is transferred to the bag.
        /// </summary>
        public static AimpPropertyBag FromOwned(IntPtr pointer)
        {
            return new AimpPropertyBag(AimpComHelper.Wrap<IAIMPPropertyListNative>(pointer), true);
        }

        /// <summary>
        /// Wraps a property list RCW; the bag does not own it.
        /// </summary>
        public AimpPropertyBag(IAIMPPropertyListNative properties)
            : this(properties, false)
        {
        }

        private AimpPropertyBag(IAIMPPropertyListNative properties, bool owns)
        {
            _properties = properties ?? throw new ArgumentNullException(nameof(properties));
            _owns = owns;
        }

        private IAIMPPropertyList2Native Properties2
        {
            get
            {
                if (_properties2 == null)
                {
                    _properties2 = (IAIMPPropertyList2Native)(object)_properties;
                }

                return _properties2;
            }
        }

        public void BeginUpdate()
        {
            _properties.BeginUpdate();
        }

        public void EndUpdate()
        {
            _properties.EndUpdate();
        }

        public int Reset()
        {
            return _properties.Reset();
        }

        public int GetInt32(int propertyId, int fallback = 0)
        {
            return _properties.GetValueAsInt32(propertyId, out var value) < 0 ? fallback : value;
        }

        public long GetInt64(int propertyId, long fallback = 0)
        {
            return _properties.GetValueAsInt64(propertyId, out var value) < 0 ? fallback : value;
        }

        public double GetFloat(int propertyId, double fallback = 0)
        {
            return _properties.GetValueAsFloat(propertyId, out var value) < 0 ? fallback : value;
        }

        public bool GetBool(int propertyId, bool fallback = false)
        {
            return _properties.GetValueAsInt32(propertyId, out var value) < 0 ? fallback : value != 0;
        }

        public void SetInt32(int propertyId, int value)
        {
            _properties.SetValueAsInt32(propertyId, value);
        }

        public void SetInt64(int propertyId, long value)
        {
            _properties.SetValueAsInt64(propertyId, value);
        }

        public void SetFloat(int propertyId, double value)
        {
            _properties.SetValueAsFloat(propertyId, value);
        }

        public void SetBool(int propertyId, bool value)
        {
            _properties.SetValueAsInt32(propertyId, value ? 1 : 0);
        }

        public string GetString(int propertyId)
        {
            var iid = AimpIids.IAIMPString;
            return _properties.GetValueAsObject(propertyId, ref iid, out var pointer) < 0
                ? null
                : AimpString.ReadAndRelease(pointer);
        }

        public void SetString(int propertyId, string value)
        {
            var pointer = AimpString.CreateNative(value);
            try
            {
                _properties.SetValueAsObject(propertyId, pointer);
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        /// <summary>
        /// Returns an owned pointer to the object stored in the property.
        /// </summary>
        public IntPtr GetObjectPointer(int propertyId, Guid iid)
        {
            return _properties.GetValueAsObject(propertyId, ref iid, out var pointer) < 0
                ? IntPtr.Zero
                : pointer;
        }

        public T GetObject<T>(int propertyId) where T : class
        {
            var iid = AimpComHelper.InterfaceId<T>();
            var pointer = GetObjectPointer(propertyId, iid);
            if (pointer == IntPtr.Zero)
            {
                return null;
            }

            try
            {
                return (T)Marshal.GetTypedObjectForIUnknown(pointer, typeof(T));
            }
            finally
            {
                Marshal.Release(pointer);
            }
        }

        public void SetObject(int propertyId, IntPtr value)
        {
            _properties.SetValueAsObject(propertyId, value);
        }

        public void SetObject(int propertyId, object instance, Type interfaceType)
        {
            var pointer = AimpComHelper.GetPointer(instance, interfaceType);
            _properties.SetValueAsObject(propertyId, pointer);
        }

        public object GetVariant(int propertyId)
        {
            var pointer = AimpVariant.Alloc(null);
            try
            {
                if (Properties2.GetValueAsVariant(propertyId, pointer) < 0)
                {
                    return null;
                }

                return AimpVariant.Read(pointer);
            }
            finally
            {
                AimpVariant.Free(pointer);
            }
        }

        public void SetVariant(int propertyId, object value)
        {
            var pointer = AimpVariant.Alloc(value);
            try
            {
                Properties2.SetValueAsVariant(propertyId, pointer);
            }
            finally
            {
                AimpVariant.Free(pointer);
            }
        }

        public void Dispose()
        {
            _properties2 = null;

            if (_owns)
            {
                Marshal.FinalReleaseComObject(_properties);
            }
        }
    }
}