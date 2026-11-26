using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Core;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Core;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// <see cref="IAimpServiceLog"/> over <c>IAIMPServiceLog</c>.
/// </summary>
internal sealed class AimpServiceLog : AimpObjectWrapper, IAimpServiceLog
{
    private readonly IAIMPServiceLogNative _native;

    public AimpServiceLog(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceLogNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public void Add(string message)
    {
        Add(message, 0);
    }

    public void Add(string message, uint flags)
    {
        if (_native == null)
        {
            return;
        }

        var text = AimpString.CreateNative(message ?? string.Empty);

        try
        {
            _native.Add2(text, flags);
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