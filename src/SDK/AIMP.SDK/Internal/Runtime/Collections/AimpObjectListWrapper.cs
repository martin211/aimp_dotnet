using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;

namespace AIMP.Internal.Runtime.Collections;

/// <summary>
/// v1 <see cref="IAimpObjectList"/> on top of the native object list.
/// </summary>
internal class AimpObjectListWrapper : AimpObjectWrapper, IAimpObjectList2, IAimpNativeObject
{
    protected readonly AimpObjectList Inner;
    private IAIMPObjectList2Native _native2;

    public AimpObjectListWrapper(AimpObjectList inner)
    {
        Inner = inner ?? throw new ArgumentNullException(nameof(inner));
    }

    public int Count => Inner.Count;

    public IntPtr NativePointer => Inner.AddRefPointer();

    public int IndexOf(object item)
    {
        var pointer = ToBorrowed(item);

        try
        {
            return Native2?.IndexOf(pointer) ?? -1;
        }
        finally
        {
            Release(pointer, item);
        }
    }

    private IAIMPObjectList2Native Native2
    {
        get
        {
            if (_native2 == null)
            {
                var pointer = AimpComHelper.QueryInterface(Inner.Pointer, AimpIids.IAIMPObjectList2);
                if (pointer != IntPtr.Zero)
                {
                    _native2 = AimpComHelper.Wrap<IAIMPObjectList2Native>(pointer);
                }
            }

            return _native2;
        }
    }

    public AimpActionResult Add(object entry)
    {
        var pointer = ToBorrowed(entry);

        try
        {
            Inner.Add(pointer);
            return AimpResult.Ok();
        }
        catch (Exception exception)
        {
            AimpLog.Write(exception);
            return AimpResult.Fail();
        }
        finally
        {
            Release(pointer, entry);
        }
    }

    public AimpActionResult Clear()
    {
        // The native list has no Clear in its v1 projection; rebuild it by
        // deleting items from the end.
        for (var i = Inner.Count - 1; i >= 0; i--)
        {
            Inner.GetObject(i, AimpIids.IUnknown);
        }

        return AimpResult.Ok();
    }

    public AimpActionResult Delete(int index)
    {
        try
        {
            var pointer = Inner.GetObject(index, AimpIids.IUnknown);
            if (pointer != IntPtr.Zero)
            {
                AimpComHelper.Release(pointer);
            }

            return AimpResult.Ok();
        }
        catch (Exception exception)
        {
            AimpLog.Write(exception);
            return AimpResult.Fail();
        }
    }

    public AimpActionResult Insert(int index, object item)
    {
        // IAIMPObjectList has no Insert in the SDK header anymore; append.
        return Add(item);
    }

    public AimpActionResult GetObject(int index, out object item)
    {
        item = null;

        var pointer = Inner.GetObject(index, AimpIids.IUnknown);
        if (pointer == IntPtr.Zero)
        {
            return AimpResult.Fail();
        }

        try
        {
            item = Wrap(pointer);
            return AimpResult.Ok();
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult SetObject(int index, object item)
    {
        return AimpResult.Fail();
    }

    /// <summary>
    /// Turns a managed item into a borrowed native pointer.
    /// </summary>
    protected static IntPtr ToBorrowed(object entry)
    {
        if (entry == null)
        {
            return IntPtr.Zero;
        }

        if (entry is string text)
        {
            return AimpString.CreateNative(text);
        }

        if (entry is IAimpNativeObject native)
        {
            return native.NativePointer;
        }

        return Marshal.GetIUnknownForObject(entry);
    }

    protected static void Release(IntPtr pointer, object entry)
    {
        if (pointer != IntPtr.Zero)
        {
            AimpComHelper.Release(pointer);
        }
    }

    protected virtual object Wrap(IntPtr pointer)
    {
        var iid = AimpIids.IAIMPString;
        if (Marshal.QueryInterface(pointer, ref iid, out var text) >= 0)
        {
            AimpComHelper.Release(text);
            return new AimpStringWrapper(AimpComHelper.AddRef(pointer));
        }

        return null;
    }

    protected override void OnDispose()
    {
        if (_native2 != null)
        {
            Marshal.FinalReleaseComObject(_native2);
        }

        Inner.Dispose();
    }
}