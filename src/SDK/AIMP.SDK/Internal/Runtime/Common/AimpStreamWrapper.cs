using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// Managed wrapper around <c>IAIMPStream</c>.
/// </summary>
internal class AimpStreamWrapper : AimpObjectWrapper, IAimpStream, IAimpNativeObject
{
    private readonly IAIMPStreamNative _native;

    public AimpStreamWrapper(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPStreamNative>(borrowedPointer);
    }

    public AimpStreamWrapper(IAIMPStreamNative native)
    {
        _native = native ?? throw new ArgumentNullException(nameof(native));
    }

    protected IAIMPStreamNative Native => _native;

    public IntPtr NativePointer
    {
        get
        {
            if (_native == null)
            {
                return IntPtr.Zero;
            }

            var unknown = Marshal.GetIUnknownForObject(_native);
            try
            {
                // The caller needs the IAIMPStream vtable, not IUnknown.
                var iid = AimpIids.IAIMPStream;
                return Marshal.QueryInterface(unknown, ref iid, out var pointer) < 0
                    ? IntPtr.Zero
                    : pointer;
            }
            finally
            {
                Marshal.Release(unknown);
            }
        }
    }

    public long GetSize()
    {
        return _native.GetSize();
    }

    public AimpActionResult SetSize(long value)
    {
        return AimpResult.From(_native.SetSize(value));
    }

    public long GetPosition()
    {
        return _native.GetPosition();
    }

    public AimpActionResult Seek(long offset, System.IO.SeekOrigin mode)
    {
        return AimpResult.From(_native.Seek(offset, (int)mode));
    }

    public int Read(byte[] buffer, int count)
    {
        if (buffer == null)
        {
            return 0;
        }

        var handle = GCHandle.Alloc(buffer, GCHandleType.Pinned);
        try
        {
            return _native.Read(handle.AddrOfPinnedObject(), count);
        }
        finally
        {
            handle.Free();
        }
    }

    public AimpActionResult Write(byte[] buffer, int count, out int written)
    {
        if (buffer == null)
        {
            written = 0;
            return AimpResult.Fail();
        }

        var handle = GCHandle.Alloc(buffer, GCHandleType.Pinned);
        try
        {
            var hr = _native.Write(handle.AddrOfPinnedObject(), count, out written);
            return AimpResult.From(hr);
        }
        finally
        {
            handle.Free();
        }
    }

    protected override void OnDispose()
    {
        Marshal.FinalReleaseComObject(_native);
    }
}