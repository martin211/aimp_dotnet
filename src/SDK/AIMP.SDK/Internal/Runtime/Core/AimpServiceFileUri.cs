using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceFileURI2"/> (implements the v1 URI contract).
/// </summary>
internal sealed class AimpServiceFileUri : AimpObjectWrapper, IAimpServiceFileURI3
{
    private readonly IAIMPServiceFileURI2Native _native;
    private readonly IAIMPServiceFileURI3Native _native3;

    public AimpServiceFileUri(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileURI2Native>(borrowedPointer);

        var pointer3 = AimpComHelper.QueryInterface(borrowedPointer, AimpIids.IAIMPServiceFileURI3);
        if (pointer3 != IntPtr.Zero)
        {
            _native3 = AimpComHelper.Wrap<IAIMPServiceFileURI3Native>(pointer3);
        }
    }

    public AimpActionResult<string> Build(string containerName, string partName)
    {
        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var container = AimpString.CreateNative(containerName ?? string.Empty);
        var part = AimpString.CreateNative(partName ?? string.Empty);

        try
        {
            var hr = _native.Build(container, part, out var result);

            return hr < 0 || result == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(result));
        }
        finally
        {
            AimpComHelper.Release(container);
            AimpComHelper.Release(part);
        }
    }

    public AimpActionResult<Tuple<string, string>> Parse(string fileUri)
    {
        if (_native == null)
        {
            return AimpResult.Fail<Tuple<string, string>>();
        }

        var text = AimpString.CreateNative(fileUri ?? string.Empty);

        try
        {
            var hr = _native.Parse(text, out var container, out var part);

            if (hr < 0)
            {
                return AimpResult.Fail<Tuple<string, string>>();
            }

            var result = new Tuple<string, string>(
                AimpString.ReadAndRelease(container),
                AimpString.ReadAndRelease(part));

            return AimpResult.Ok(result);
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult ChangeFileExt(string fileUri, string extension, FileUriFlag flag)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var original = AimpString.CreateNative(fileUri ?? string.Empty);
        var current = original;
        var ext = AimpString.CreateNative(extension ?? string.Empty);

        try
        {
            return AimpResult.From(_native.ChangeFileExt(ref current, ext, (uint)flag));
        }
        finally
        {
            if (current != original)
            {
                AimpComHelper.Release(original);
            }

            AimpComHelper.Release(current);
            AimpComHelper.Release(ext);
        }
    }

    public AimpActionResult<string> ExtractFileExt(string fileUri, FileUriFlag flag)
    {
        int Callback(IntPtr text, out IntPtr value) =>
            _native.ExtractFileExt(text, out value, (uint)flag);

        return Extract(fileUri, Callback);
    }

    public AimpActionResult<string> ExtractFileName(string fileUri)
    {
        int Callback(IntPtr text, out IntPtr value) => _native.ExtractFileName(text, out value);
        return Extract(fileUri, Callback);
    }

    public AimpActionResult<string> ExtractFileParentDirName(string fileUri)
    {
        int Callback(IntPtr text, out IntPtr value) => _native.ExtractFileParentDirName(text, out value);
        return Extract(fileUri, Callback);
    }

    public AimpActionResult<string> ExtractFileParentName(string fileUri)
    {
        int Callback(IntPtr text, out IntPtr value) => _native.ExtractFileParentName(text, out value);
        return Extract(fileUri, Callback);
    }

    public AimpActionResult<string> ExtractFilePath(string fileUri)
    {
        int Callback(IntPtr text, out IntPtr value) => _native.ExtractFilePath(text, out value);
        return Extract(fileUri, Callback);
    }

    public AimpActionResult IsURL(string fileUri)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var text = AimpString.CreateNative(fileUri ?? string.Empty);

        try
        {
            return AimpResult.From(_native.IsURL(text));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult<string> GetScheme(string fileUri)
    {
        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var text = AimpString.CreateNative(fileUri ?? string.Empty);

        try
        {
            var hr = _native.GetScheme(text, out var result);

            return hr < 0 || result == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(result));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult<string> ProcessEnvironmentVariables(string fileUri, FileUriEnvironmentFlag flag)
    {
        if (_native3 == null)
        {
            return AimpResult.Fail<string>();
        }

        var original = AimpString.CreateNative(fileUri ?? string.Empty);
        var current = original;

        try
        {
            var hr = _native3.ProcessEnvironmentVariables(ref current, (uint)flag);

            if (hr < 0 || current == IntPtr.Zero)
            {
                return AimpResult.Fail<string>();
            }

            if (current == original)
            {
                original = IntPtr.Zero;
            }
            else
            {
                AimpComHelper.Release(original);
                original = IntPtr.Zero;
            }

            var value = AimpString.ReadAndRelease(current);
            current = IntPtr.Zero;
            return AimpResult.Ok(value);
        }
        finally
        {
            AimpComHelper.Release(original);
            AimpComHelper.Release(current);
        }
    }

    private delegate int ExtractCallback(IntPtr text, out IntPtr value);

    private AimpActionResult<string> Extract(string fileUri, ExtractCallback callback)
    {
        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var text = AimpString.CreateNative(fileUri ?? string.Empty);

        try
        {
            var hr = callback(text, out var result);

            return hr < 0 || result == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(result));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }

        if (_native3 != null)
        {
            Marshal.FinalReleaseComObject(_native3);
        }
    }
}