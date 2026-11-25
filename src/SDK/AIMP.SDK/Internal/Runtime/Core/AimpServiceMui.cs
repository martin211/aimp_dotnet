using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MUIManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.MUIManager;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceMUI"/>.
/// </summary>
internal sealed class AimpServiceMui : AimpObjectWrapper, IAimpServiceMUI
{
    private readonly IAIMPServiceMUINative _native;

    public AimpServiceMui(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceMUINative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public string GetName()
    {
        return _native == null ? string.Empty : Read(_native.GetName);
    }

    public string GetValue(string key)
    {
        if (_native == null)
        {
            return string.Empty;
        }

        var text = AimpString.CreateNative(key ?? string.Empty);

        try
        {
            return _native.GetValue(text, out var result) < 0 || result == IntPtr.Zero
                ? string.Empty
                : AimpString.ReadAndRelease(result);
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public string GetValuePart(string key, int index)
    {
        if (_native == null)
        {
            return string.Empty;
        }

        var text = AimpString.CreateNative(key ?? string.Empty);

        try
        {
            return _native.GetValuePart(text, index, out var result) < 0 || result == IntPtr.Zero
                ? string.Empty
                : AimpString.ReadAndRelease(result);
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    private string Read(GetStringCallback callback)
    {
        if (callback == null)
        {
            return string.Empty;
        }

        return callback(out var result) < 0 || result == IntPtr.Zero
            ? string.Empty
            : AimpString.ReadAndRelease(result);
    }

    private delegate int GetStringCallback(out IntPtr value);

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}