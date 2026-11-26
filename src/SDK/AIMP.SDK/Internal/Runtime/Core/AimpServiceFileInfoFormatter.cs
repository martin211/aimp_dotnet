using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceFileInfoFormatter"/>.
/// </summary>
internal sealed class AimpServiceFileInfoFormatter : AimpObjectWrapper, IAimpServiceFileInfoFormatter
{
    private readonly IAIMPServiceFileInfoFormatterNative _native;

    public AimpServiceFileInfoFormatter(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileInfoFormatterNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<string> Format(string template, IAimpFileInfo fileInfo)
    {
        return Format(template, fileInfo, 0);
    }

    public AimpActionResult<string> Format(string template, IAimpFileInfo fileInfo, int formatterId)
    {
        if (formatterId != 0)
        {
            AimpApiGuard.Require(6, 0, "IAimpServiceFileInfoFormatter.Format(formatterId)");
        }

        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var text = AimpString.CreateNative(template ?? string.Empty);
        var info = AimpBridgeHelper.GetPointer(fileInfo, typeof(IAIMPFileInfoNative));

        try
        {
            var hr = _native.Format(text, info, formatterId, IntPtr.Zero, out var result);

            return hr < 0 || result == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(result));
        }
        finally
        {
            AimpComHelper.Release(text);
            AimpComHelper.Release(info);
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