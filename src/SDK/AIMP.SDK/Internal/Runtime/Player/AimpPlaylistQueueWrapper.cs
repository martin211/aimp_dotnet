using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.PlayList;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpPlaylistQueue"/> over the native queue.
    /// </summary>
    internal sealed class AimpPlaylistQueueWrapper : AimpObjectWrapper, IAimpPlaylistQueue
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPPlaylistQueueNative _native;
        private readonly IAIMPPlaylistQueue2Native _native2;
        private readonly AimpPropertyBag _properties;

        private AimpPlaylistQueueListenerBridge _listener;
        private IntPtr _listenerPointer;

        private AimpPlaylistQueueListenerHandler _contentChanged;
        private AimpPlaylistQueueListenerHandler _stateChanged;

        public AimpPlaylistQueueWrapper(IntPtr ownedPointer, IntPtr ownedQueue2Pointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPPlaylistQueueNative>(ownedPointer);
            _properties = AimpPropertyBag.FromOwned(
                AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPPropertyList));

            if (ownedQueue2Pointer != IntPtr.Zero)
            {
                _native2 = AimpComHelper.Wrap<IAIMPPlaylistQueue2Native>(ownedQueue2Pointer);
            }

            EnsureListener();
        }

        public bool IsSuspended
        {
            get => _properties != null && _properties.GetBool(AimpPropId.PlaylistQueueSuspended);
            set => _properties?.SetBool(AimpPropId.PlaylistQueueSuspended, value);
        }

        public event AimpPlaylistQueueListenerHandler ContentChanged
        {
            add => _contentChanged += value;
            remove => _contentChanged -= value;
        }

        public event AimpPlaylistQueueListenerHandler StateChanged
        {
            add => _stateChanged += value;
            remove => _stateChanged -= value;
        }

        internal void RaiseContentChanged()
        {
            _contentChanged?.Invoke(this);
        }

        internal void RaiseStateChanged()
        {
            _stateChanged?.Invoke(this);
        }

        private void EnsureListener()
        {
            if (_listener != null || _native2 == null)
            {
                return;
            }

            _listener = new AimpPlaylistQueueListenerBridge(this);
            _listenerPointer = AimpComHelper.GetPointer(
                _listener,
                typeof(IAIMPPlaylistQueueListenerNative));

            _native2.ListenerAdd(_listenerPointer);
        }

        public AimpActionResult Add(IAimpPlaylistItem item, bool insertAtBeginning)
        {
            var pointer = AimpBridgeHelper.GetPointer(item, typeof(IAIMPPlaylistItemNative));

            try
            {
                return AimpResult.From(_native.Add(pointer, insertAtBeginning ? 1 : 0));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult AddList(IList<IAimpPlaylistItem> items, bool insertAtBeginning)
        {
            using (var list = AimpObjectList.Create())
            {
                if (items != null)
                {
                    foreach (var item in items)
                    {
                        if (item == null)
                        {
                            continue;
                        }

                        var pointer = AimpBridgeHelper.GetPointer(item, typeof(IAIMPPlaylistItemNative));

                        try
                        {
                            list.Add(pointer);
                        }
                        finally
                        {
                            AimpComHelper.Release(pointer);
                        }
                    }
                }

                return AimpResult.From(_native.AddList(list.AddRefInterfacePointer(), insertAtBeginning ? 1 : 0));
            }
        }

        public AimpActionResult Delete(IAimpPlaylistItem item)
        {
            var pointer = AimpBridgeHelper.GetPointer(item, typeof(IAIMPPlaylistItemNative));

            try
            {
                return AimpResult.From(_native.Delete(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Delete(IAimpPlaylist playList)
        {
            var pointer = AimpBridgeHelper.GetPointer(playList, typeof(IAIMPPlaylistNative));

            try
            {
                return AimpResult.From(_native.Delete2(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Move(IAimpPlaylistItem item, int index)
        {
            var pointer = AimpBridgeHelper.GetPointer(item, typeof(IAIMPPlaylistItemNative));

            try
            {
                return AimpResult.From(_native.Move(pointer, index));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Move(int index, int targetIndex)
        {
            return AimpResult.From(_native.Move2(index, targetIndex));
        }

        public AimpActionResult<IAimpPlaylistItem> GetItem(int index)
        {
            var iid = AimpIids.IAIMPPlaylistItem;
            var hr = _native.GetItem(index, ref iid, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpPlaylistItem>(hr, null)
                : AimpResult.Ok<IAimpPlaylistItem>(new AimpPlaylistItemWrapper(pointer));
        }

        public int GetItemCount()
        {
            return _native.GetItemCount();
        }

        protected override void OnDispose()
        {
            if (_listener != null && _native2 != null)
            {
                _native2.ListenerRemove(_listenerPointer);
                AimpComHelper.Release(_listenerPointer);
                _listenerPointer = IntPtr.Zero;
                _listener = null;
            }

            _properties?.Dispose();

            if (_native2 != null)
            {
                Marshal.FinalReleaseComObject(_native2);
            }

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}