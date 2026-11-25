using System;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpGroupingPreset"/> over the native preset.
/// </summary>
internal class AimpGroupingPresetWrapper : AimpObjectWrapper, IAimpGroupingPreset
{
    private readonly AimpPropertyBag _properties;
    private readonly IntPtr _pointer;

    public AimpGroupingPresetWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;

        // Any grouping preset is an IAIMPPropertyList. Do not QI the base
        // IAIMPMLGroupingPreset IID: an IAIMPMLGroupingPresetStandard object
        // answers E_NOINTERFACE for it.
        _properties = new AimpPropertyBag(AimpComHelper.Wrap<IAIMPPropertyListNative>(ownedPointer));
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    protected IntPtr GetObjectPointer(int propertyId, Guid iid)
    {
        return _properties.GetObjectPointer(propertyId, iid);
    }

    protected void SetObject(int propertyId, IntPtr value)
    {
        _properties.SetObject(propertyId, value);
    }

    public string Custom
    {
        get => _properties.GetString(AimpMlPropId.GroupingPresetCustom);
        set => _properties.SetString(AimpMlPropId.GroupingPresetCustom, value);
    }

    public string Id
    {
        get => _properties.GetString(AimpMlPropId.GroupingPresetId);
        set => _properties.SetString(AimpMlPropId.GroupingPresetId, value);
    }

    public string Name
    {
        get => _properties.GetString(AimpMlPropId.GroupingPresetName);
        set => _properties.SetString(AimpMlPropId.GroupingPresetName, value);
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
    }
}