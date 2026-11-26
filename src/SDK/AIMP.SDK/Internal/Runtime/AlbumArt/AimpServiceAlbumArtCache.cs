using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.AlbumArt;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.AlbumArt.Services;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.AlbumArt;

/// <summary>
/// v1 <see cref="IAimpServiceAlbumArtCache"/>.
/// </summary>
internal sealed class AimpServiceAlbumArtCache : AimpObjectWrapper, IAimpServiceAlbumArtCache
{
    private readonly IAIMPServiceAlbumArtCacheNative _native;

    public AimpServiceAlbumArtCache(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceAlbumArtCacheNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult Flush() => _native == null ? AimpResult.Fail() : AimpResult.From(_native.Flush());

    public AimpActionResult<IAimpImageContainer> Get(string key)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpImageContainer>();
        }

        var text = AimpString.CreateNative(key ?? string.Empty);

        try
        {
            var hr = _native.Get(text, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpImageContainer>()
                : AimpResult.Ok<IAimpImageContainer>(new AimpImageContainerWrapper(pointer));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult Put(string key, IAimpImageContainer image)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var text = AimpString.CreateNative(key ?? string.Empty);
        var pointer = AimpBridgeHelper.GetPointer(image, typeof(IAIMPImageContainerNative));

        try
        {
            return AimpResult.From(_native.Put(text, ref pointer));
        }
        finally
        {
            AimpComHelper.Release(text);
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult Remove(string key)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var text = AimpString.CreateNative(key ?? string.Empty);

        try
        {
            return AimpResult.From(_native.Remove(text));
        }
        finally
        {
            AimpComHelper.Release(text);
        }
    }

    public AimpActionResult<Tuple<int, int>> Stat()
    {
        return _native == null || _native.Stat(out var size, out var count) < 0
            ? AimpResult.Fail<Tuple<int, int>>()
            : AimpResult.Ok(new Tuple<int, int>((int)size, (int)count));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}