using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Runtime.Player;
using AIMP.SDK;
using AIMP.SDK.Player.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for <see cref="IAimpExtensionPlaybackQueue"/> and
    /// <see cref="IAimpExtensionPlaybackQueue2"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class PlaybackQueueBridge :
        IAIMPExtensionPlaybackQueueNative,
        IAIMPExtensionPlaybackQueue2Native
    {
        private readonly IAimpExtensionPlaybackQueue _extension;
        private readonly IAimpExtensionPlaybackQueue2 _extension2;

        public PlaybackQueueBridge(IAimpExtensionPlaybackQueue extension)
        {
            _extension = extension ?? throw new ArgumentNullException(nameof(extension));
            _extension2 = extension as IAimpExtensionPlaybackQueue2;
        }

        public int GetNext(IntPtr current, uint flags, IntPtr queueItem)
        {
            return Invoke(current, flags, queueItem, true);
        }

        public int GetPrev(IntPtr current, uint flags, IntPtr queueItem)
        {
            return Invoke(current, flags, queueItem, false);
        }

        public void OnSelect(IntPtr item, IntPtr queueItem)
        {
            Safe.Run(() =>
            {
                var playlistItem = item == IntPtr.Zero
                    ? null
                    : new AimpPlaylistItemWrapper(AimpComHelper.AddRef(item));
                var queue = WrapQueueItem(queueItem);

                try
                {
                    _extension.OnSelect(playlistItem, queue);
                }
                finally
                {
                    playlistItem?.Dispose();
                    queue?.Dispose();
                }
            });
        }

        public int GetInfo(IntPtr current, out int position, out int size)
        {
            var resultPosition = 0;
            var resultSize = 0;

            if (_extension2 == null)
            {
                position = 0;
                size = 0;
                return Safe.E_NOTIMPL;
            }

            var hr = Safe.Run(() =>
            {
                var item = current == IntPtr.Zero
                    ? null
                    : new AimpPlaylistItemWrapper(AimpComHelper.AddRef(current));

                try
                {
                    var result = _extension2.GetInfo(item);

                    if (result.ResultType == ActionResultType.OK && result.Result != null)
                    {
                        resultPosition = result.Result.Position;
                        resultSize = result.Result.Size;
                    }

                    return (int)result.ResultType;
                }
                finally
                {
                    item?.Dispose();
                }
            });

            position = resultPosition;
            size = resultSize;
            return hr;
        }

        private int Invoke(IntPtr current, uint flags, IntPtr queueItem, bool next)
        {
            return Safe.Run(() =>
            {
                var value = (PlaybackQueueFlags)flags;
                var currentObject = WrapCurrent(current, value);
                var queue = WrapQueueItem(queueItem);

                try
                {
                    var result = next
                        ? _extension.GetNext(currentObject, value, queue)
                        : _extension.GetPrev(currentObject, value, queue);

                    return (int)result.ResultType;
                }
                finally
                {
                    (currentObject as IDisposable)?.Dispose();
                    queue?.Dispose();
                }
            });
        }

        private static object WrapCurrent(IntPtr current, PlaybackQueueFlags flags)
        {
            if (current == IntPtr.Zero)
            {
                return null;
            }

            return flags == PlaybackQueueFlags.StartFromItem
                ? (object)new AimpPlaylistItemWrapper(AimpComHelper.AddRef(current))
                : AimpPlaylistWrapper.FromBorrowed(current);
        }

        private static AimpPlaybackQueueItemWrapper WrapQueueItem(IntPtr pointer)
        {
            return pointer == IntPtr.Zero
                ? null
                : new AimpPlaybackQueueItemWrapper(AimpComHelper.AddRef(pointer));
        }
    }
}