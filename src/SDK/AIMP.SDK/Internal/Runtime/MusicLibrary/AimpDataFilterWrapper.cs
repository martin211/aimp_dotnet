using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpDataFilter"/> over the native <c>IAIMPMLDataFilter</c>.
/// </summary>
internal sealed class AimpDataFilterWrapper : AimpDataFilterGroupWrapper, IAimpDataFilter
{
    private readonly IAIMPMLDataFilterNative _native;

    public AimpDataFilterWrapper(IntPtr ownedPointer)
        : base(ownedPointer)
    {
        // The group wrapper takes ownership of the same reference; the filter
        // wrapper only needs the extra IAIMPMLDataFilter methods.
        _native = AimpComHelper.WrapBorrowed<IAIMPMLDataFilterNative>(ownedPointer);
    }

    public int Offset
    {
        get => GetInt32(AimpMlPropId.FilterOffset);
        set => SetInt32(AimpMlPropId.FilterOffset, value);
    }

    public int Limit
    {
        get => GetInt32(AimpMlPropId.FilterLimit);
        set => SetInt32(AimpMlPropId.FilterLimit, value);
    }

    public IAimpObjectList SortByList
    {
        get
        {
            var pointer = GetObjectPointer(AimpMlPropId.FilterSortByList, AimpIids.IAIMPObjectList);
            return pointer == IntPtr.Zero
                ? null
                : new AimpObjectListWrapper(new AimpObjectList(pointer));
        }
        set { SetObject(AimpMlPropId.FilterSortByList, (value as IAimpNativeObject)?.NativePointer ?? IntPtr.Zero); }
    }

    public string SearchString
    {
        get => GetString(AimpMlPropId.FilterSearchString);
        set => SetString(AimpMlPropId.FilterSearchString, value);
    }

    public int AlphaBeticIndex
    {
        get => GetInt32(AimpMlPropId.FilterAlphabeticIndex);
        set => SetInt32(AimpMlPropId.FilterAlphabeticIndex, value);
    }

    public AimpActionResult Assign(IAimpDataFilter source)
    {
        var native = source as IAimpNativeObject;
        return native == null
            ? AimpResult.Fail()
            : AimpResult.From(_native.Assign(native.NativePointer));
    }

    public AimpActionResult<IAimpDataFilter> Clone()
    {
        var hr = _native.Clone(out var pointer);
        return hr < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpDataFilter>()
            : AimpResult.Ok<IAimpDataFilter>(new AimpDataFilterWrapper(pointer));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }

        base.OnDispose();
    }
}