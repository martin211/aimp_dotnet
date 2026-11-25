using System;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpDataFieldFilter"/> over the native field filter.
/// </summary>
internal sealed class AimpDataFieldFilterWrapper : AimpObjectWrapper, IAimpDataFieldFilter
{
    private readonly AimpPropertyBag _properties;
    private readonly IntPtr _pointer;

    public AimpDataFieldFilterWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        var native = AimpComHelper.Wrap<IAIMPMLDataFieldFilterNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)native);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    public string Field
    {
        get => _properties.GetString(AimpMlPropId.FieldFilterField);
        set => _properties.SetString(AimpMlPropId.FieldFilterField, value);
    }

    public FieldFilterOperationType Operation
    {
        get => (FieldFilterOperationType)_properties.GetInt32(AimpMlPropId.FieldFilterOperation);
        set => _properties.SetInt32(AimpMlPropId.FieldFilterOperation, (int)value);
    }

    public object Value1
    {
        get => _properties.GetVariant(AimpMlPropId.FieldFilterValue1);
        set => _properties.SetVariant(AimpMlPropId.FieldFilterValue1, value);
    }

    public object Value2
    {
        get => _properties.GetVariant(AimpMlPropId.FieldFilterValue2);
        set => _properties.SetVariant(AimpMlPropId.FieldFilterValue2, value);
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
    }
}