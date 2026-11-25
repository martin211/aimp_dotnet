using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Player;
using AIMP.SDK.Player.Objects;

namespace AIMP.Internal.Runtime.Player;

/// <summary>
/// v1 <see cref="IAimpServicePlaybackQueue"/>.
/// </summary>
internal sealed class AimpServicePlaybackQueue : AimpObjectWrapper, IAimpServicePlaybackQueue
{
    private readonly IAIMPServicePlaybackQueue2Native _native;

    public AimpServicePlaybackQueue(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServicePlaybackQueue2Native>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<IAimpPlaybackQueueItem> GetNextTrack()
    {
        return _native == null || _native.GetNextTrack(out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpPlaybackQueueItem>()
            : AimpResult.Ok<IAimpPlaybackQueueItem>(new AimpPlaybackQueueItemWrapper(pointer));
    }

    public AimpActionResult<IAimpPlaybackQueueItem> GetPrevTrack()
    {
        return _native == null || _native.GetPrevTrack(out var pointer) < 0 || pointer == IntPtr.Zero
            ? AimpResult.Fail<IAimpPlaybackQueueItem>()
            : AimpResult.Ok<IAimpPlaybackQueueItem>(new AimpPlaybackQueueItemWrapper(pointer));
    }

    public AimpActionResult NotifyChanged()
    {
        return _native == null ? AimpResult.Fail() : AimpResult.From(_native.NotifyChanged(IntPtr.Zero));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}