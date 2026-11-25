using System;
using AIMP.SDK;

namespace AIMP.Internal.Runtime.Common;

/// <summary>
/// Helpers that translate raw HRESULT values of the native AIMP API into
/// <see cref="AimpActionResult"/> results consumed by plugin code.
/// </summary>
internal static class AimpResult
{
    public static AimpActionResult Ok()
    {
        return new AimpActionResult(ActionResultType.OK);
    }

    public static AimpActionResult Fail()
    {
        return new AimpActionResult(ActionResultType.Fail);
    }

    public static AimpActionResult From(int hr)
    {
        return hr < 0 ? new AimpActionResult(ToResult(hr)) : Ok();
    }

    public static AimpActionResult<T> Ok<T>(T value)
    {
        return new AimpActionResult<T>(ActionResultType.OK, value);
    }

    public static AimpActionResult<T1, T2> Ok<T1, T2>(T1 value1, T2 value2)
    {
        return new AimpActionResult<T1, T2>(ActionResultType.OK, value1, value2);
    }

    public static AimpActionResult<T1, T2> Fail<T1, T2>()
    {
        return new AimpActionResult<T1, T2>(ActionResultType.Fail, default, default);
    }

    public static AimpActionResult<T> Fail<T>()
    {
        return new AimpActionResult<T>(ActionResultType.Fail);
    }

    public static AimpActionResult<T> From<T>(int hr, T value)
    {
        return hr < 0 ? new AimpActionResult<T>(ToResult(hr)) : new AimpActionResult<T>(ActionResultType.OK, value);
    }

    public static ActionResultType ToResult(int hr)
    {
        return (ActionResultType)unchecked((uint)hr);
    }

    public static string ReadString(IntPtr pointer)
    {
        return AimpString.ReadAndRelease(pointer);
    }
}