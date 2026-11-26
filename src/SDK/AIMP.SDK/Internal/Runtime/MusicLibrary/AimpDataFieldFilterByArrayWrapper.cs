using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;

namespace AIMP.Internal.Runtime.MusicLibrary;

/// <summary>
/// v1 <see cref="IAimpDataFieldFilterByArray"/> over the native filter.
/// </summary>
internal sealed class AimpDataFieldFilterByArrayWrapper : AimpObjectWrapper, IAimpDataFieldFilterByArray
{
    private readonly IAIMPMLDataFieldFilterByArrayNative _native;
    private readonly AimpPropertyBag _properties;

    public AimpDataFieldFilterByArrayWrapper(IntPtr ownedPointer)
    {
        _native = AimpComHelper.Wrap<IAIMPMLDataFieldFilterByArrayNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
    }

    public string Field
    {
        get => _properties.GetString(AimpMlPropId.FieldFilterByArrayField);
        set => _properties.SetString(AimpMlPropId.FieldFilterByArrayField, value);
    }

    public AimpActionResult<IList<object>> GetData()
    {
        if (_native.GetData(IntPtr.Zero, out var count) < 0 || count <= 0)
        {
            return AimpResult.Ok<IList<object>>(new List<object>());
        }

        var array = Marshal.AllocHGlobal(IntPtr.Size * count);
        try
        {
            // Count is not reliable for the first pass in all AIMP versions;
            // the SDK requires two calls. The second call fills the array.
            if (_native.GetData(array, out count) < 0)
            {
                return AimpResult.Fail<IList<object>>();
            }

            var values = new List<object>(count);
            for (var i = 0; i < count; i++)
            {
                var pointer = Marshal.ReadIntPtr(array, i * IntPtr.Size);
                values.Add(AimpVariant.Read(pointer));
            }

            return AimpResult.Ok<IList<object>>(values);
        }
        finally
        {
            Marshal.FreeHGlobal(array);
        }
    }

    public AimpActionResult SetData(IList<object> values)
    {
        var count = values?.Count ?? 0;
        var array = AimpVariant.AllocArray(values, out count);

        try
        {
            return AimpResult.From(_native.SetData(array, count));
        }
        finally
        {
            AimpVariant.FreeArray(array, count);
        }
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
    }
}