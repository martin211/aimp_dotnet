using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.PlayList;

namespace AIMP.Internal.Runtime.Player;

/// <summary>
/// <see cref="IAimpPlaylistProperties"/> over <c>IAIMPPlaylistProperties</c>.
/// </summary>
internal sealed class AimpPlaylistPropertiesWrapper : AimpObjectWrapper, IAimpPlaylistProperties
{
    private readonly IAIMPPlaylistPropertiesNative _native;

    public AimpPlaylistPropertiesWrapper(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPPlaylistPropertiesNative>(borrowedPointer);
    }

    public void BeginUpdate()
    {
        _native?.BeginUpdate();
    }

    public void EndUpdate()
    {
        _native?.EndUpdate();
    }

    public AimpActionResult<string> GetCustomValue(string name)
    {
        if (_native == null)
        {
            return AimpResult.Fail<string>();
        }

        var key = AimpString.CreateNative(name ?? string.Empty);

        try
        {
            var hr = _native.GetCustomValue(key, out var value);

            return hr < 0 || value == IntPtr.Zero
                ? AimpResult.Fail<string>()
                : AimpResult.Ok(AimpString.ReadAndRelease(value));
        }
        finally
        {
            AimpComHelper.Release(key);
        }
    }

    public AimpActionResult SetCustomValue(string name, string value)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var key = AimpString.CreateNative(name ?? string.Empty);
        var text = AimpString.CreateNative(value ?? string.Empty);

        try
        {
            return AimpResult.From(_native.SetCustomValue(key, text));
        }
        finally
        {
            AimpComHelper.Release(key);
            AimpComHelper.Release(text);
        }
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}