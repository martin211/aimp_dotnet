using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpDataFilterGroup"/> over the native filter group.
/// </summary>
internal class AimpDataFilterGroupWrapper : AimpObjectWrapper, IAimpDataFilterGroup
{
    private readonly IAIMPMLDataFilterGroupNative _native;
    private readonly AimpPropertyBag _properties;
    private readonly IntPtr _pointer;

    public AimpDataFilterGroupWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        _native = AimpComHelper.Wrap<IAIMPMLDataFilterGroupNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    internal IAIMPMLDataFilterGroupNative NativeRaw => _native;

    protected int GetInt32(int propertyId, int fallback = 0)
    {
        return _properties.GetInt32(propertyId, fallback);
    }

    protected void SetInt32(int propertyId, int value)
    {
        _properties.SetInt32(propertyId, value);
    }

    protected string GetString(int propertyId)
    {
        return _properties.GetString(propertyId);
    }

    protected void SetString(int propertyId, string value)
    {
        _properties.SetString(propertyId, value);
    }

    protected IntPtr GetObjectPointer(int propertyId, Guid iid)
    {
        return _properties.GetObjectPointer(propertyId, iid);
    }

    protected void SetObject(int propertyId, IntPtr value)
    {
        _properties.SetObject(propertyId, value);
    }

    public FilterGroupOperationType Operation
    {
        get => (FilterGroupOperationType)_properties.GetInt32(AimpMlPropId.FilterGroupOperation);
        set => _properties.SetInt32(AimpMlPropId.FilterGroupOperation, (int)value);
    }

    public void BeginUpdate()
    {
        _properties.BeginUpdate();
    }

    public void EndUpdate()
    {
        _properties.EndUpdate();
    }

    public AimpActionResult<IAimpDataFieldFilter> Add(
        string field,
        object value1,
        object value2,
        FieldFilterOperationType operation)
    {
        var fieldPointer = AimpString.CreateNative(field);
        var first = AimpVariant.Alloc(value1);
        var second = AimpVariant.Alloc(value2);

        try
        {
            var hr = _native.Add(fieldPointer, first, second, (int)operation, out var pointer);
            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpDataFieldFilter>()
                : AimpResult.Ok<IAimpDataFieldFilter>(new AimpDataFieldFilterWrapper(pointer));
        }
        finally
        {
            AimpComHelper.Release(fieldPointer);
            AimpVariant.Free(first);
            AimpVariant.Free(second);
        }
    }

    public AimpActionResult<IAimpDataFieldFilterByArray> Add(string field, object[] values, int count)
    {
        var fieldPointer = AimpString.CreateNative(field);
        var array = AimpVariant.AllocArray(values, out count);

        try
        {
            var hr = _native.Add2(fieldPointer, array, count, out var pointer);
            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpDataFieldFilterByArray>()
                : AimpResult.Ok<IAimpDataFieldFilterByArray>(new AimpDataFieldFilterByArrayWrapper(pointer));
        }
        finally
        {
            AimpComHelper.Release(fieldPointer);
            AimpVariant.FreeArray(array, count);
        }
    }

    public AimpActionResult<IAimpDataFilterGroup> AddGroup()
    {
        var hr = _native.AddGroup(out var pointer);
        return hr < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpDataFilterGroup>()
            : AimpResult.Ok<IAimpDataFilterGroup>(new AimpDataFilterGroupWrapper(pointer));
    }

    public AimpActionResult Clear()
    {
        return AimpResult.From(_native.Clear());
    }

    public AimpActionResult Delete(int index)
    {
        return AimpResult.From(_native.Delete(index));
    }

    public AimpActionResult<TFilter> GetChild<TFilter>(int index) where TFilter : IAimpFilter
    {
        var iid = InterfaceIdOf<TFilter>();

        return _native.GetChild(index, ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<TFilter>()
            : AimpResult.Ok((TFilter)CreateChild<TFilter>(pointer));
    }

    public int GetChildCount()
    {
        return _native.GetChildCount();
    }

    private static Guid InterfaceIdOf<TFilter>() where TFilter : IAimpFilter
    {
        var target = typeof(TFilter);

        if (typeof(IAimpDataFieldFilterByArray).IsAssignableFrom(target))
        {
            return AimpIids.IAIMPMLDataFieldFilterByArray;
        }

        if (typeof(IAimpDataFilterGroup).IsAssignableFrom(target))
        {
            return AimpIids.IAIMPMLDataFilterGroup;
        }

        return AimpIids.IAIMPMLDataFieldFilter;
    }

    private static object CreateChild<TFilter>(IntPtr pointer) where TFilter : IAimpFilter
    {
        var target = typeof(TFilter);

        if (typeof(IAimpDataFieldFilterByArray).IsAssignableFrom(target))
        {
            return new AimpDataFieldFilterByArrayWrapper(pointer);
        }

        if (typeof(IAimpDataFilter).IsAssignableFrom(target))
        {
            return new AimpDataFilterWrapper(pointer);
        }

        if (typeof(IAimpDataFilterGroup).IsAssignableFrom(target))
        {
            return new AimpDataFilterGroupWrapper(pointer);
        }

        return new AimpDataFieldFilterWrapper(pointer);
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
        Marshal.FinalReleaseComObject(_native);
    }
}