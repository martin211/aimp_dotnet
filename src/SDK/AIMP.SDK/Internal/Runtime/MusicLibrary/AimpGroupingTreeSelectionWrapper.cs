using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpGroupingTreeSelection"/> over the native selection.
/// </summary>
internal sealed class AimpGroupingTreeSelectionWrapper : AimpObjectWrapper, IAimpGroupingTreeSelection
{
    private readonly IAIMPMLGroupingTreeSelectionNative _native;

    public AimpGroupingTreeSelectionWrapper(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPMLGroupingTreeSelectionNative>(borrowedPointer);
    }

    public int GetCount()
    {
        return _native.GetCount();
    }

    public AimpActionResult<string, object> GetValue(int index)
    {
        var value = AimpVariant.Alloc(null);

        try
        {
            var hr = _native.GetValue(index, out var fieldName, value);
            if (hr < 0)
            {
                return AimpResult.Fail<string, object>();
            }

            var name = fieldName == IntPtr.Zero ? null : AimpString.ReadAndRelease(fieldName);
            return AimpResult.Ok(name, AimpVariant.Read(value));
        }
        finally
        {
            AimpVariant.Free(value);
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