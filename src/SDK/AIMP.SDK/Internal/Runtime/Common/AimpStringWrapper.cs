using System;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// Managed wrapper around <c>IAIMPString</c>.
/// </summary>
internal sealed class AimpStringWrapper : AimpObjectWrapper, IAimpString, IAimpNativeObject
{
    private readonly AimpString _inner;

    public AimpStringWrapper(AimpString inner)
    {
        _inner = inner ?? throw new ArgumentNullException(nameof(inner));
    }

    public AimpStringWrapper(IntPtr ownedPointer)
    {
        _inner = new AimpString(ownedPointer, null);
    }

    public IntPtr NativePointer => _inner.AddRefPointer();

    private IAIMPStringNative Native => _inner.Native;

    public string Value
    {
        get => _inner.Value;
        set => _inner.Value = value;
    }

    public int GetAimpHashCode()
    {
        return Native.GetHashCodeNative();
    }

    public void Recalculate()
    {
    }

    public AimpActionResult<char> GetChar(int index)
    {
        return Get(index);
    }

    public AimpActionResult<char> Get(int index)
    {
        var hr = Native.Get(index, out var character);
        return AimpResult.From(hr, (char)character);
    }

    public string GetData()
    {
        return _inner.Value;
    }

    public int GetLength()
    {
        return Native.GetLength();
    }

    public AimpActionResult SetChar(int index, char c)
    {
        return Set(index, c);
    }

    public AimpActionResult Set(int index, char c)
    {
        return AimpResult.From(Native.Set(index, c));
    }

    public AimpActionResult SetData(string chars, int charsCount)
    {
        return AimpResult.From(Native.SetData(chars, charsCount));
    }

    public AimpActionResult Add(IAimpString str)
    {
        return AimpResult.From(Native.Add(PointerOf(str)));
    }

    public AimpActionResult Add(string chars, int charsCount)
    {
        return AimpResult.From(Native.Add2(chars, charsCount));
    }

    public AimpActionResult ChangeCase(AimpStringCase mode)
    {
        return AimpResult.From(Native.ChangeCase((int)mode));
    }

    public AimpActionResult<IAimpString> Clone()
    {
        var hr = Native.Clone(out var clone);
        return hr < 0
            ? AimpResult.Fail<IAimpString>()
            : AimpResult.Ok<IAimpString>(new AimpStringWrapper(clone));
    }

    public AimpActionResult<int> Compare(IAimpString str, bool ignoreCase)
    {
        var hr = Native.Compare(PointerOf(str), out var result, ignoreCase ? 1 : 0);
        return AimpResult.From(hr, result);
    }

    public AimpActionResult<int> Compare(string chars, bool ignoreCase)
    {
        var hr = Native.Compare2(chars, chars?.Length ?? 0, out var result, ignoreCase ? 1 : 0);
        return AimpResult.From(hr, result);
    }

    public AimpActionResult Delete(int index, int count)
    {
        return AimpResult.From(Native.Delete(index, count));
    }

    public AimpActionResult<int> Find(IAimpString str, AimpStringFindFlags flags, int startFromIndex)
    {
        var hr = Native.Find(PointerOf(str), out var index, (int)flags, startFromIndex);
        return AimpResult.From(hr, index);
    }

    public AimpActionResult<int> Find(string chars, AimpStringFindFlags flags, int startFromIndex)
    {
        var hr = Native.Find2(chars, chars?.Length ?? 0, out var index, (int)flags, startFromIndex);
        return AimpResult.From(hr, index);
    }

    public AimpActionResult Insert(int index, IAimpString str)
    {
        return AimpResult.From(Native.Insert(index, PointerOf(str)));
    }

    public AimpActionResult Insert(int index, string chars)
    {
        return AimpResult.From(Native.Insert2(index, chars, chars?.Length ?? 0));
    }

    public AimpActionResult Replace(IAimpString oldPattern, IAimpString newPattern, AimpStringFindFlags flags)
    {
        return AimpResult.From(Native.Replace(PointerOf(oldPattern), PointerOf(newPattern), (int)flags));
    }

    public AimpActionResult Replace(
        string oldPatternChars,
        string newPatternChars,
        AimpStringFindFlags flags)
    {
        return AimpResult.From(Native.Replace2(
            oldPatternChars,
            oldPatternChars?.Length ?? 0,
            newPatternChars,
            newPatternChars?.Length ?? 0,
            (int)flags));
    }

    public AimpActionResult<IAimpString> SubString(int index, int count)
    {
        var hr = Native.SubString(index, count, out var pointer);
        return hr < 0
            ? AimpResult.Fail<IAimpString>()
            : AimpResult.Ok<IAimpString>(new AimpStringWrapper(pointer));
    }

    public void Release()
    {
        Dispose();
    }

    protected override void OnDispose()
    {
        _inner.Dispose();
    }

    private static IntPtr PointerOf(IAimpString value)
    {
        if (value is IAimpNativeObject native)
        {
            var pointer = native.NativePointer;
            return pointer;
        }

        return value == null ? IntPtr.Zero : AimpString.CreateNative(value.GetData());
    }

    public override string ToString()
    {
        return _inner.Value;
    }
}