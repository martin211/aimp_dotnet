using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// Managed wrapper around <c>IAIMPConfig</c>.
/// </summary>
internal class AimpConfigWrapper : AimpObjectWrapper, IAimpConfig
{
    protected readonly IAIMPConfigNative _native;

    public AimpConfigWrapper(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPConfigNative>(borrowedPointer);
    }

    public AimpConfigWrapper(IAIMPConfigNative native, bool owns)
    {
        _native = native ?? throw new ArgumentNullException(nameof(native));
    }

    public AimpActionResult Delete(string keyPath)
    {
        return AimpResult.From(_native.Delete(Create(keyPath)));
    }

    public AimpActionResult<float> GetValueAsFloat(string keyPath)
    {
        var hr = _native.GetValueAsFloat(Create(keyPath), out var value);
        return AimpResult.From(hr, (float)value);
    }

    public AimpActionResult<int> GetValueAsInt32(string keyPath)
    {
        var hr = _native.GetValueAsInt32(Create(keyPath), out var value);
        return AimpResult.From(hr, value);
    }

    public AimpActionResult<long> GetValueAsInt64(string keyPath)
    {
        var hr = _native.GetValueAsInt64(Create(keyPath), out var value);
        return AimpResult.From(hr, value);
    }

    public AimpActionResult<IAimpStream> GetValueAsStream(string keyPath)
    {
        var hr = _native.GetValueAsStream(Create(keyPath), out var value);
        return hr < 0 || value == IntPtr.Zero
            ? AimpResult.Fail<IAimpStream>()
            : AimpResult.Ok<IAimpStream>(new AimpStreamWrapper(value));
    }

    public AimpActionResult<string> GetValueAsString(string keyPath)
    {
        var hr = _native.GetValueAsString(Create(keyPath), out var value);
        return hr < 0 ? AimpResult.Fail<string>() : AimpResult.Ok(AimpResult.ReadString(value));
    }

    public AimpActionResult SetValueAsFloat(string keyPath, float value)
    {
        return AimpResult.From(_native.SetValueAsFloat(Create(keyPath), value));
    }

    public AimpActionResult SetValueAsInt32(string keyPath, int value)
    {
        return AimpResult.From(_native.SetValueAsInt32(Create(keyPath), value));
    }

    public AimpActionResult SetValueAsInt64(string keyPath, long value)
    {
        return AimpResult.From(_native.SetValueAsInt64(Create(keyPath), value));
    }

    public AimpActionResult SetValueAsStream(string keyPath, IAimpStream stream)
    {
        var pointer = stream is IAimpNativeObject native ? native.NativePointer : IntPtr.Zero;

        try
        {
            return AimpResult.From(_native.SetValueAsStream(Create(keyPath), pointer));
        }
        finally
        {
            if (pointer != IntPtr.Zero)
            {
                Marshal.Release(pointer);
            }
        }
    }

    public AimpActionResult SetValueAsString(string keyPath, string value)
    {
        return AimpResult.From(_native.SetValueAsString(Create(keyPath), Create(value)));
    }

    protected override void OnDispose()
    {
        Marshal.FinalReleaseComObject(_native);
    }

    private static IntPtr Create(string value)
    {
        return AimpString.CreateNative(value ?? string.Empty);
    }
}