using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player;

/// <summary>
/// v1 <see cref="IAimpPlaybackQueueItem"/> over a native property list.
/// </summary>
internal sealed class AimpPlaybackQueueItemWrapper : AimpObjectWrapper, IAimpPlaybackQueueItem, IAimpNativeObject
{
    private readonly IntPtr _pointer;
    private readonly IAIMPPropertyListNative _native;
    private readonly AimpPropertyBag _properties;
    private object _userData;

    public AimpPlaybackQueueItemWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        _native = AimpComHelper.Wrap<IAIMPPropertyListNative>(ownedPointer);
        _properties = new AimpPropertyBag(_native);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    public object UserData
    {
        get => _userData;
        set => _userData = value;
    }

    public IAimpPlaylistItem PlaylistItem
    {
        get
        {
            var pointer = _properties.GetObjectPointer(
                AimpPropId.PlaybackQueueItemPlaylistItem,
                AimpIids.IAIMPPlaylistItem);

            return pointer == IntPtr.Zero ? null : new AimpPlaylistItemWrapper(pointer);
        }
        set
        {
            var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPPlaylistItemNative));

            try
            {
                _properties.SetObject(AimpPropId.PlaybackQueueItemPlaylistItem, pointer);
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }
    }

    public double Offset
    {
        get => _properties.GetFloat(AimpPropId.PlaybackQueueItemOffset);
        set => _properties.SetFloat(AimpPropId.PlaybackQueueItemOffset, value);
    }

    protected override void OnDispose()
    {
        _properties.Dispose();

        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}