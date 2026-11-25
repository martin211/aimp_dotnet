using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// v1 <see cref="IAimpErrorInfo"/> over <c>IAIMPErrorInfo</c>.
/// </summary>
internal sealed class AimpErrorInfoWrapper : AimpObjectWrapper, IAimpErrorInfo
{
    private readonly IAIMPErrorInfoNative _native;

    public AimpErrorInfoWrapper(IntPtr ownedPointer)
    {
        _native = AimpComHelper.Wrap<IAIMPErrorInfoNative>(ownedPointer);
    }

    public AimpActionResult<ErrorInfo> GetInfo()
    {
        var hr = _native.GetInfo(out var errorCode, out var message, out var details);
        if (hr < 0)
        {
            return AimpResult.Fail<ErrorInfo>();
        }

        return AimpResult.Ok(new ErrorInfo(
            errorCode,
            AimpString.ReadAndRelease(message),
            AimpString.ReadAndRelease(details)));
    }

    public AimpActionResult<string> GetInfoFormatted()
    {
        var hr = _native.GetInfoFormatted(out var text);
        return hr < 0 || text == IntPtr.Zero
            ? AimpResult.Fail<string>()
            : AimpResult.Ok(AimpString.ReadAndRelease(text));
    }

    public void SetInfo(int errorCode, string message, string details)
    {
        var messagePointer = message == null ? IntPtr.Zero : AimpString.CreateNative(message);
        var detailsPointer = details == null ? IntPtr.Zero : AimpString.CreateNative(details);

        try
        {
            _native.SetInfo(errorCode, messagePointer, detailsPointer);
        }
        finally
        {
            AimpComHelper.Release(messagePointer);
            AimpComHelper.Release(detailsPointer);
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