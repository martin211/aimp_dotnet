using System;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;

namespace AIMP.Internal.Runtime.Collections;

/// <summary>
/// v1 <c>IAimpObjectList&lt;string&gt;</c>.
/// </summary>
internal sealed class AimpStringList : AimpObjectWrapper, IAimpObjectList<string>, IAimpNativeObject
{
    private readonly AimpObjectList _inner;

    public AimpStringList(AimpObjectList inner)
    {
        _inner = inner ?? throw new ArgumentNullException(nameof(inner));
    }

    public int Count => _inner.Count;

    public IntPtr NativePointer => _inner.AddRefPointer();

    public AimpActionResult Add(string entry)
    {
        try
        {
            _inner.Add(entry ?? string.Empty);
            return AimpResult.Ok();
        }
        catch (Exception exception)
        {
            AimpLog.Write(exception);
            return AimpResult.Fail();
        }
    }

    public AimpActionResult Clear()
    {
        return AimpResult.Fail();
    }

    public AimpActionResult Delete(int index)
    {
        return AimpResult.Fail();
    }

    public AimpActionResult Insert(int index, string item)
    {
        return Add(item);
    }

    public AimpActionResult GetObject(int index, out string item)
    {
        item = _inner.GetString(index);
        return item == null ? AimpResult.Fail() : AimpResult.Ok();
    }

    public AimpActionResult SetObject(int index, string item)
    {
        return AimpResult.Fail();
    }

    protected override void OnDispose()
    {
        _inner.Dispose();
    }
}