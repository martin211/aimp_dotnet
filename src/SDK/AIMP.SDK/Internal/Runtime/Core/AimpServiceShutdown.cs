using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Core;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Core;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceShutdown"/>.
/// </summary>
internal sealed class AimpServiceShutdown : AimpObjectWrapper, IAimpServiceShutdown
{
    private readonly IAIMPServiceShutdownNative _native;

    public AimpServiceShutdown(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceShutdownNative>(borrowedPointer);
    }

    public AimpActionResult Restart(string arguments)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var text = AimpString.CreateNative(arguments ?? string.Empty);

        try
        {
            return AimpResult.From(_native.Restart(text));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult Shutdown(ShutdownType shutdownType)
    {
        return _native == null
            ? AimpResult.Fail()
            : AimpResult.From(_native.Shutdown((uint)shutdownType));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}