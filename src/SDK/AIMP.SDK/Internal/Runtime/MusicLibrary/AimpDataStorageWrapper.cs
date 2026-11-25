using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpDataStorage"/> over the native <c>IAIMPMLDataStorage</c>.
/// </summary>
internal class AimpDataStorageWrapper : AimpObjectWrapper, IAimpDataStorage, IAimpDataStorage2, IAimpNativeObject
{
    private readonly IAIMPMLDataStorageNative _native;
    private readonly AimpPropertyBag _properties;
    private readonly IntPtr _pointer;

    public AimpDataStorageWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        _native = AimpComHelper.Wrap<IAIMPMLDataStorageNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    public string Id => _properties.GetString(AimpMlPropId.DataStorageId);

    public string Caption => _properties.GetString(AimpMlPropId.DataStorageCaption);

    public IAimpGroupingPreset GroupingPreset
    {
        get
        {
            var pointer = _properties.GetObjectPointer(
                AimpMlPropId.DataStorageGroupingPreset,
                AimpIids.IAIMPMLGroupingPreset);

            return pointer == IntPtr.Zero ? null : new AimpGroupingPresetWrapper(pointer);
        }
        set
        {
            var native = value as IAimpNativeObject;
            _properties.SetObject(AimpMlPropId.DataStorageGroupingPreset, native?.NativePointer ?? IntPtr.Zero);
        }
    }

    public AimpActionResult<object> CreateObject()
    {
        var storage = _native as IAIMPMLDataStorage2Native;
        if (storage == null)
        {
            return AimpResult.Fail<object>();
        }

        var iid = AimpIids.IAIMPMLDataFilter;
        return storage.CreateObject(ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<object>()
            : AimpResult.Ok<object>(new AimpDataFilterWrapper(pointer));
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
        Marshal.FinalReleaseComObject(_native);
    }
}