using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// Managed wrapper around <c>IAIMPMemoryStream</c>.
/// </summary>
internal sealed class AimpMemoryStreamWrapper : AimpStreamWrapper, IAimpMemoryStream
{
    private IAIMPMemoryStreamNative _memoryStream;

    public AimpMemoryStreamWrapper(IntPtr ownedPointer)
        : base(ownedPointer)
    {
    }

    public AimpActionResult<byte[]> GetData()
    {
        var native = MemoryStreamNative;
        if (native == null)
        {
            return AimpResult.Fail<byte[]>();
        }

        var pointer = native.GetData();
        var size = GetSize();
        if (pointer == IntPtr.Zero || size <= 0)
        {
            return AimpResult.Ok(Array.Empty<byte>());
        }

        var data = new byte[(int)size];
        Marshal.Copy(pointer, data, 0, data.Length);
        return AimpResult.Ok(data);
    }

    private IAIMPMemoryStreamNative MemoryStreamNative
    {
        get
        {
            if (_memoryStream != null)
            {
                return _memoryStream;
            }

            var stream = Native;
            if (stream == null)
            {
                return null;
            }

            var unknown = Marshal.GetIUnknownForObject(stream);
            try
            {
                var iid = AimpIids.IAIMPMemoryStream;
                return Marshal.QueryInterface(unknown, ref iid, out var pointer) < 0
                    ? null
                    : (_memoryStream = AimpComHelper.Wrap<IAIMPMemoryStreamNative>(pointer));
            }
            finally
            {
                Marshal.Release(unknown);
            }
        }
    }

    protected override void OnDispose()
    {
        if (_memoryStream != null)
        {
            Marshal.FinalReleaseComObject(_memoryStream);
            _memoryStream = null;
        }

        base.OnDispose();
    }
}