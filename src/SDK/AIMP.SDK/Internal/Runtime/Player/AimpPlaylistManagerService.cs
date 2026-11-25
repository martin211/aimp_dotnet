using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.PlayList;
using AIMP.SDK.PlayList.Extensions;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpServicePlaylistManager"/>.
    /// </summary>
    internal sealed class AimpPlaylistManagerService : AimpObjectWrapper, IAimpServicePlaylistManager
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPServicePlaylistManager2Native _native;
        private IAimpPlaylistQueue _queue;

        public AimpPlaylistManagerService(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPServicePlaylistManager2Native>(ownedPointer);
        }

        public bool IsExists => _native != null;

        public IAimpPlaylistQueue PlaylistQueue
        {
            get
            {
                if (_queue != null)
                {
                    return _queue;
                }

                var queue = AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPPlaylistQueue);

                if (queue == IntPtr.Zero)
                {
                    return null;
                }

                var queue2 = AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPPlaylistQueue2);

                _queue = new AimpPlaylistQueueWrapper(queue, queue2);
                return _queue;
            }
        }

        public AimpActionResult<IAimpPlaylist> CreatePlaylist(string name, bool isActive)
        {
            var text = string.IsNullOrEmpty(name) ? IntPtr.Zero : AimpString.CreateNative(name);

            try
            {
                var hr = _native.CreatePlaylist(text, isActive ? 1 : 0, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.From<IAimpPlaylist>(hr, null)
                    : AimpResult.Ok<IAimpPlaylist>(new AimpPlaylistWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult<IAimpPlaylist> CreatePlaylistFromFile(string fileName, bool isActive)
        {
            if (string.IsNullOrEmpty(fileName))
            {
                throw new ArgumentNullException(nameof(fileName), "Playlist file name cannot be empty.");
            }

            var text = AimpString.CreateNative(fileName ?? string.Empty);

            try
            {
                var hr = _native.CreatePlaylistFromFile(text, isActive ? 1 : 0, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.From<IAimpPlaylist>(hr, null)
                    : AimpResult.Ok<IAimpPlaylist>(new AimpPlaylistWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult<IAimpPlaylist> GetActivePlaylist()
        {
            var hr = _native.GetActivePlaylist(out var pointer);
            return WrapPlaylist(hr, pointer);
        }

        public AimpActionResult SetActivePlaylist(IAimpPlaylist playList)
        {
            var pointer = AimpBridgeHelper.GetPointer(playList, typeof(IAIMPPlaylistNative));

            try
            {
                return AimpResult.From(_native.SetActivePlaylist(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult<IAimpPlaylist> GetPlayingPlaylist()
        {
            var hr = _native.GetPlayingPlaylist(out var pointer);
            return WrapPlaylist(hr, pointer);
        }

        public AimpActionResult<IAimpPlaylist> GetLoadedPlaylist(int index)
        {
            var hr = _native.GetLoadedPlaylist(index, out var pointer);
            return WrapPlaylist(hr, pointer);
        }

        public AimpActionResult<IAimpPlaylist> GetLoadedPlaylistById(string id)
        {
            var text = AimpString.CreateNative(id ?? string.Empty);

            try
            {
                var hr = _native.GetLoadedPlaylistByID(text, out var pointer);
                return WrapPlaylist(hr, pointer);
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult<IAimpPlaylist> GetLoadedPlaylistByName(string name)
        {
            var text = AimpString.CreateNative(name ?? string.Empty);

            try
            {
                var hr = _native.GetLoadedPlaylistByName(text, out var pointer);
                return WrapPlaylist(hr, pointer);
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public int GetLoadedPlaylistCount()
        {
            return _native?.GetLoadedPlaylistCount() ?? 0;
        }

        public AimpActionResult<IAimpExtensionPlaylistPreimageFactory> GetPreimageFactory(int index)
        {
            var hr = _native.GetPreimageFactory(index, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpExtensionPlaylistPreimageFactory>(hr, null)
                : AimpResult.Ok<IAimpExtensionPlaylistPreimageFactory>(
                    new AimpPlaylistPreimageFactoryWrapper(pointer));
        }

        public AimpActionResult<IAimpExtensionPlaylistPreimageFactory> GetPreimageFactoryById(string id)
        {
            var text = AimpString.CreateNative(id ?? string.Empty);

            try
            {
                var hr = _native.GetPreimageFactoryByID(text, out var pointer);

                return hr < 0 || pointer == IntPtr.Zero
                    ? AimpResult.From<IAimpExtensionPlaylistPreimageFactory>(hr, null)
                    : AimpResult.Ok<IAimpExtensionPlaylistPreimageFactory>(
                        new AimpPlaylistPreimageFactoryWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public int GetPreimageFactoryCount()
        {
            return _native?.GetPreimageFactoryCount() ?? 0;
        }

        private static AimpActionResult<IAimpPlaylist> WrapPlaylist(int hr, IntPtr pointer)
        {
            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpPlaylist>(hr, null)
                : AimpResult.Ok<IAimpPlaylist>(new AimpPlaylistWrapper(pointer));
        }

        protected override void OnDispose()
        {
            (_queue as IDisposable)?.Dispose();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}