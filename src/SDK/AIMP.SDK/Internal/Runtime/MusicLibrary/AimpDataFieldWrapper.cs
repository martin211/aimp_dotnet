using System;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpDataField"/> over the native <c>IAIMPMLDataField</c>.
/// </summary>
internal sealed class AimpDataFieldWrapper : AimpObjectWrapper, IAimpDataField
{
    private readonly AimpPropertyBag _properties;

    public AimpDataFieldWrapper(IntPtr ownedPointer)
    {
        var native = AimpComHelper.Wrap<IAIMPMLDataFieldNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)native);
    }

    public string Custom
    {
        get => _properties.GetString(AimpMlPropId.FieldCustom);
        set => _properties.SetString(AimpMlPropId.FieldCustom, value);
    }

    public string Name
    {
        get => _properties.GetString(AimpMlPropId.FieldName);
        set => _properties.SetString(AimpMlPropId.FieldName, value);
    }

    public AimpDataFieldType Type
    {
        get => (AimpDataFieldType)_properties.GetInt32(AimpMlPropId.FieldType);
        set => _properties.SetInt32(AimpMlPropId.FieldType, (int)value);
    }

    public AimpDataFieldFlagsType Flags
    {
        get => (AimpDataFieldFlagsType)_properties.GetInt32(AimpMlPropId.FieldFlags);
        set => _properties.SetInt32(AimpMlPropId.FieldFlags, (int)value);
    }

    public ImageType Image
    {
        get => (ImageType)_properties.GetInt32(AimpMlPropId.FieldImage);
        set => _properties.SetInt32(AimpMlPropId.FieldImage, (int)value);
    }

    public string DisplayValue
    {
        get => _properties.GetString(AimpMlPropId.FieldDisplayValue);
        set => _properties.SetString(AimpMlPropId.FieldDisplayValue, value);
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
    }
}