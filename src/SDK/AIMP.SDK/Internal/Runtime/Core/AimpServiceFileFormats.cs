using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceFileFormats"/>.
/// </summary>
internal sealed class AimpServiceFileFormats : AimpObjectWrapper, IAimpServiceFileFormats
{
    private readonly IAIMPServiceFileFormatsNative _native;

    public AimpServiceFileFormats(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileFormatsNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<string> GetFormats(FileFormats flags)
    {
        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var hr = _native.GetFormats((uint)flags, out var text);

        return hr < 0 || text == IntPtr.Zero
            ? AimpResult.Fail<string>()
            : AimpResult.Ok(AimpString.ReadAndRelease(text));
    }

    public AimpActionResult IsSupported(string fileName, FileFormats flags)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var text = AimpString.CreateNative(fileName ?? string.Empty);

        try
        {
            return AimpResult.From(_native.IsSupported(text, (uint)flags));
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
    }
}