using System;
using System.Drawing;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.AlbumArt
{
    /// <summary>
    /// v1 <see cref="IAimpImageContainer"/>.
    /// </summary>
    internal sealed class AimpImageContainerWrapper :
        AimpObjectWrapper,
        IAimpImageContainer,
        IAimpNativeObject
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPImageContainerNative _native;
        private readonly IAIMPHashCodeNative _hashCode;

        public AimpImageContainerWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPImageContainerNative>(ownedPointer);

            var hash = AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPHashCode);
            if (hash != IntPtr.Zero)
            {
                _hashCode = AimpComHelper.Wrap<IAIMPHashCodeNative>(hash);
            }
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        public AimpActionResult<IAimpImage> CreateImage()
        {
            // The image wrapper is not projected yet; the container itself is enough
            // for caching and album art scenarios.
            return AimpResult.Fail<IAimpImage>();
        }

        public AimpActionResult<Tuple<Size, AimpImageFormat>> GetInfo()
        {
            var hr = _native.GetInfo(out var size, out var format);

            return hr < 0
                ? AimpResult.Fail<Tuple<Size, AimpImageFormat>>()
                : AimpResult.Ok(new Tuple<Size, AimpImageFormat>(
                    new Size(size.Width, size.Height),
                    (AimpImageFormat)format));
        }

        public AimpActionResult<byte[]> GetData()
        {
            var size = _native.GetDataSize();

            if (size == 0)
            {
                return AimpResult.Ok(Array.Empty<byte>());
            }

            var pointer = _native.GetData();

            if (pointer == IntPtr.Zero)
            {
                return AimpResult.Fail<byte[]>();
            }

            var data = new byte[size];
            Marshal.Copy(pointer, data, 0, (int)size);

            return AimpResult.Ok(data);
        }

        public AimpActionResult SetData(byte[] data)
        {
            if (data == null)
            {
                return AimpResult.Fail();
            }

            var hr = _native.SetDataSize((uint)data.Length);
            if (hr < 0)
            {
                return AimpResult.From(hr);
            }

            var pointer = _native.GetData();
            if (pointer != IntPtr.Zero)
            {
                Marshal.Copy(data, 0, pointer, data.Length);
            }

            return AimpResult.Ok();
        }

        public uint GetDataSize() => _native.GetDataSize();

        public AimpActionResult SetDataSize(long value) => AimpResult.From(_native.SetDataSize((uint)value));

        public int GetAimpHashCode() => _hashCode?.GetHashCode() ?? 0;

        public void Recalculate() => _hashCode?.Recalculate();

        protected override void OnDispose()
        {
            if (_hashCode != null)
            {
                Marshal.FinalReleaseComObject(_hashCode);
            }

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}