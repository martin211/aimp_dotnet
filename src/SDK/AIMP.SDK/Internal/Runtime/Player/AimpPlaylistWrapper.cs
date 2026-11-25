using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.PlayList;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpPlaylist"/> over the native <c>IAIMPPlaylist</c>.
    /// </summary>
    internal sealed class AimpPlaylistWrapper : AimpObjectWrapper, IAimpPlaylist, IAimpNativeObject
    {
        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int SortCompareProc(IntPtr item1, IntPtr item2, IntPtr userData);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int DeleteFilterProc(IntPtr item, IntPtr userData);

        private sealed class SortContext
        {
            public object Data;
            public Func<IAimpPlaylistItem, IAimpPlaylistItem, object, PlaylistSortCompareResult> Compare;
        }

        private sealed class DeleteContext
        {
            public object Data;
            public Func<IAimpPlaylistItem, object, bool> Filter;
        }

        private readonly IntPtr _pointer;
        private readonly IAIMPPlaylistNative _native;
        private readonly AimpPropertyBag _properties;

        private IntPtr _listenerPointer;
        private AimpPlaylistListenerBridge _listener;

        private AimpPlayListHandler _activated;
        private AimpPlayListHandler _removed;
        private PlayListChangedHandler _changed;
        private AimpPlayListHandler _scanningBegin;
        private AimpPlayListHandler<ScanningProgressEventArgs> _scanningProgress;
        private AimpPlayListHandler<ScanningEndEventArgs> _scanningEnd;

        public AimpPlaylistWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPPlaylistNative>(AimpComHelper.AddRef(ownedPointer));
            _properties = AimpPropertyBag.FromOwned(
                AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPPropertyList));
        }

        public static AimpPlaylistWrapper FromBorrowed(IntPtr pointer)
        {
            return pointer == IntPtr.Zero ? null : new AimpPlaylistWrapper(AimpComHelper.AddRef(pointer));
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        public AimpActionResult<IAimpPlaylistProperties> GetProperties()
        {
            AimpApiGuard.Require(6, 0, "IAimpPlaylistProperties");
            var pointer = AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPPlaylistProperties);
            if (pointer == IntPtr.Zero)
            {
                return AimpResult.Fail<IAimpPlaylistProperties>();
            }

            try
            {
                return AimpResult.Ok<IAimpPlaylistProperties>(new AimpPlaylistPropertiesWrapper(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        private AimpPropertyBag Properties => _properties;

        #region Properties

        public string Id => Properties == null ? null : Properties.GetString(AimpPropId.PlaylistId);

        public string Name
        {
            get => Properties == null ? null : Properties.GetString(AimpPropId.PlaylistName);
            set
            {
                if (Properties != null)
                {
                    Properties.SetString(AimpPropId.PlaylistName, value);
                }
            }
        }

        public bool ReadOnly
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistReadOnly);
            set
            {
                if (Properties != null)
                {
                    Properties.SetBool(AimpPropId.PlaylistReadOnly, value);
                }
            }
        }

        public IAimpPlaylistItem FocusedItem
        {
            get
            {
                var pointer = Properties?.GetObjectPointer(
                    AimpPropId.PlaylistFocusedObject,
                    AimpIids.IAIMPPlaylistItem);

                return pointer == null || pointer == IntPtr.Zero
                    ? null
                    : new AimpPlaylistItemWrapper(pointer.Value);
            }
            set
            {
                if (Properties == null)
                {
                    return;
                }

                var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPPlaylistItemNative));

                try
                {
                    Properties.SetObject(AimpPropId.PlaylistFocusedObject, pointer);
                }
                finally
                {
                    AimpComHelper.Release(pointer);
                }
            }
        }

        public IAimpPlaylistGroup FocusedGroup
        {
            get
            {
                var pointer = Properties?.GetObjectPointer(
                    AimpPropId.PlaylistFocusedObject,
                    AimpIids.IAIMPPlaylistGroup);

                return pointer == null || pointer == IntPtr.Zero
                    ? null
                    : new AimpPlaylistGroupWrapper(pointer.Value);
            }
            set
            {
                if (Properties == null)
                {
                    return;
                }

                var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPPlaylistGroupNative));

                try
                {
                    Properties.SetObject(AimpPropId.PlaylistFocusedObject, pointer);
                }
                finally
                {
                    AimpComHelper.Release(pointer);
                }
            }
        }

        public bool GroupingOverridden
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistGroupingOverridden);
            set => Properties?.SetBool(AimpPropId.PlaylistGroupingOverridden, value);
        }

        public bool Grouping
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistGrouping);
            set => Properties?.SetBool(AimpPropId.PlaylistGrouping, value);
        }

        public string GroupingTemplate
        {
            get => Properties?.GetString(AimpPropId.PlaylistGroupingTemplate);
            set => Properties?.SetString(AimpPropId.PlaylistGroupingTemplate, value);
        }

        public bool GroupingAutomerg
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistGroupingAutomerging);
            set => Properties?.SetBool(AimpPropId.PlaylistGroupingAutomerging, value);
        }

        public bool FormattingOverride
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistFormattingOverridden);
            set => Properties?.SetBool(AimpPropId.PlaylistFormattingOverridden, value);
        }

        public string FormattingLine1Template
        {
            get => Properties?.GetString(AimpPropId.PlaylistFormattingLine1);
            set => Properties?.SetString(AimpPropId.PlaylistFormattingLine1, value);
        }

        public string FormattingLine2Template
        {
            get => Properties?.GetString(AimpPropId.PlaylistFormattingLine2);
            set => Properties?.SetString(AimpPropId.PlaylistFormattingLine2, value);
        }

        public bool ViewOverride
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewOverridden);
            set => Properties?.SetBool(AimpPropId.PlaylistViewOverridden, value);
        }

        public bool ViewDuration
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewDuration);
            set => Properties?.SetBool(AimpPropId.PlaylistViewDuration, value);
        }

        public bool ViewExpandButtons
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewExpandButtons);
            set => Properties?.SetBool(AimpPropId.PlaylistViewExpandButtons, value);
        }

        public bool ViewMarks
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewMarks);
            set => Properties?.SetBool(AimpPropId.PlaylistViewMarks, value);
        }

        public bool ViewNumbers
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewNumbers);
            set => Properties?.SetBool(AimpPropId.PlaylistViewNumbers, value);
        }

        public bool ViewAbsoluteNumbers
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewNumbersAbsolute);
            set => Properties?.SetBool(AimpPropId.PlaylistViewNumbersAbsolute, value);
        }

        public bool ViewSecondLine
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewSecondLine);
            set => Properties?.SetBool(AimpPropId.PlaylistViewSecondLine, value);
        }

        public bool ViewSwitches
        {
            get => Properties != null && Properties.GetBool(AimpPropId.PlaylistViewSwitches);
            set => Properties?.SetBool(AimpPropId.PlaylistViewSwitches, value);
        }

        public int FocusIndex
        {
            get => Properties?.GetInt32(AimpPropId.PlaylistFocusIndex) ?? 0;
            set => Properties?.SetInt32(AimpPropId.PlaylistFocusIndex, value);
        }

        public int PlaybackCursor
        {
            get => Properties?.GetInt32(AimpPropId.PlaylistPlaybackCursor) ?? 0;
            set => Properties?.SetInt32(AimpPropId.PlaylistPlaybackCursor, value);
        }

        public int PlayingIndex
        {
            get => Properties?.GetInt32(AimpPropId.PlaylistPlayingIndex) ?? 0;
            set => Properties?.SetInt32(AimpPropId.PlaylistPlayingIndex, value);
        }

        public double Duration => Properties?.GetFloat(AimpPropId.PlaylistDuration) ?? 0d;

        public double Size => Properties?.GetFloat(AimpPropId.PlaylistSize) ?? 0d;

        public IAimpPlaylistPreimage PreImage
        {
            get
            {
                var pointer = Properties?.GetObjectPointer(
                    AimpPropId.PlaylistPreimage,
                    AimpIids.IAIMPPlaylistPreimage);

                return pointer == null || pointer == IntPtr.Zero
                    ? null
                    : AimpPlaylistPreimageWrapper.Wrap(pointer.Value);
            }
            set
            {
                if (Properties == null)
                {
                    return;
                }

                var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPPlaylistPreimageNative));

                try
                {
                    Properties.SetObject(AimpPropId.PlaylistPreimage, pointer);
                }
                finally
                {
                    AimpComHelper.Release(pointer);
                }
            }
        }

        #endregion

        #region Events

        public event AimpPlayListHandler Activated
        {
            add
            {
                EnsureListener();
                _activated += value;
            }
            remove => _activated -= value;
        }

        public event AimpPlayListHandler Removed
        {
            add
            {
                EnsureListener();
                _removed += value;
            }
            remove => _removed -= value;
        }

        public event PlayListChangedHandler Changed
        {
            add
            {
                EnsureListener();
                _changed += value;
            }
            remove => _changed -= value;
        }

        public event AimpPlayListHandler ScanningBegin
        {
            add
            {
                EnsureListener();
                _scanningBegin += value;
            }
            remove => _scanningBegin -= value;
        }

        public event AimpPlayListHandler<ScanningProgressEventArgs> ScanningProgress
        {
            add
            {
                EnsureListener();
                _scanningProgress += value;
            }
            remove => _scanningProgress -= value;
        }

        public event AimpPlayListHandler<ScanningEndEventArgs> ScanningEnd
        {
            add
            {
                EnsureListener();
                _scanningEnd += value;
            }
            remove => _scanningEnd -= value;
        }

        internal void RaiseChanged(uint flags)
        {
            _changed?.Invoke(this, (PlaylistNotifyType)flags);
        }

        internal void RaiseActivated()
        {
            _activated?.Invoke(this);
        }

        internal void RaiseRemoved()
        {
            _removed?.Invoke(this);
        }

        internal void RaiseScanningBegin()
        {
            _scanningBegin?.Invoke(this);
        }

        internal void RaiseScanningProgress(double progress)
        {
            _scanningProgress?.Invoke(this, new ScanningProgressEventArgs(progress));
        }

        internal void RaiseScanningEnd(bool hasChanges, bool canceled)
        {
            _scanningEnd?.Invoke(this, new ScanningEndEventArgs(hasChanges, canceled));
        }

        private void EnsureListener()
        {
            if (_listener != null)
            {
                return;
            }

            _listener = new AimpPlaylistListenerBridge(this);
            _listenerPointer = AimpComHelper.GetPointer(_listener, typeof(IAIMPPlaylistListenerNative));
            _native.ListenerAdd(_listenerPointer);
        }

        private void RemoveListener()
        {
            if (_listener == null)
            {
                return;
            }

            _native.ListenerRemove(_listenerPointer);
            AimpComHelper.Release(_listenerPointer);
            _listenerPointer = IntPtr.Zero;
            _listener = null;
        }

        #endregion

        #region Adding

        public AimpActionResult Add(string fileUrl, PlaylistFlags flags, PlaylistFilePosition filePosition)
        {
            if (string.IsNullOrEmpty(fileUrl))
            {
                throw new ArgumentNullException(nameof(fileUrl), "File URI cannot be empty.");
            }

            var text = AimpString.CreateNative(fileUrl ?? string.Empty);

            try
            {
                return AimpResult.From(_native.Add(text, (uint)flags, (int)filePosition));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult Add(IAimpFileInfo fileInfo, PlaylistFlags flags, PlaylistFilePosition filePosition)
        {
            var pointer = AimpBridgeHelper.GetPointer(fileInfo, typeof(IAIMPFileInfoNative));

            try
            {
                return AimpResult.From(_native.Add(pointer, (uint)flags, (int)filePosition));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult AddList(
            IList<string> fileUrlList,
            PlaylistFlags flags,
            PlaylistFilePosition filePosition)
        {
            if (fileUrlList == null || fileUrlList.Count == 0)
            {
                throw new ArgumentNullException(nameof(fileUrlList), "File list cannot be empty.");
            }

            using (var list = AimpObjectList.Create())
            {
                if (fileUrlList != null)
                {
                    foreach (var fileUrl in fileUrlList)
                    {
                        list.Add(fileUrl ?? string.Empty);
                    }
                }

                var listPointer = list.AddRefInterfacePointer();
                var hr = _native.AddList(listPointer, (uint)flags, (int)filePosition);

                if (hr < 0)
                {
                    AimpLog.Write(
                        $"IAIMPPlaylist.AddList(string) failed: hr=0x{hr.ToString("X8")}, count={list.Count}, flags={flags}, position={filePosition}.");
                }

                return AimpResult.From(hr);
            }
        }

        public AimpActionResult AddList(
            IList<IAimpFileInfo> fileUrlList,
            PlaylistFlags flags,
            PlaylistFilePosition filePosition)
        {
            using (var list = AimpObjectList.Create())
            {
                if (fileUrlList != null)
                {
                    foreach (var fileInfo in fileUrlList)
                    {
                        if (fileInfo == null)
                        {
                            continue;
                        }

                        var pointer = AimpBridgeHelper.GetPointer(fileInfo, typeof(IAIMPFileInfoNative));

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

                return AimpResult.From(
                    _native.AddList(list.AddRefPointer(), (uint)flags, (int)filePosition));
            }
        }

        #endregion

        #region Deleting

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

        public AimpActionResult Delete(int index)
        {
            return AimpResult.From(_native.Delete2(index));
        }

        public AimpActionResult Delete(
            PlaylistDeleteFlags deleteFlags,
            object customFilterData,
            Func<IAimpPlaylistItem, object, bool> filterFunc)
        {
            if (filterFunc == null)
            {
                return AimpResult.From(_native.Delete3((uint)deleteFlags, IntPtr.Zero, IntPtr.Zero));
            }

            var context = new DeleteContext { Data = customFilterData, Filter = filterFunc };
            var handle = GCHandle.Alloc(context);

            DeleteFilterProc callback = OnDeleteFilter;

            try
            {
                return AimpResult.From(
                    _native.Delete3(
                        (uint)deleteFlags,
                        Marshal.GetFunctionPointerForDelegate(callback),
                        GCHandle.ToIntPtr(handle)));
            }
            finally
            {
                handle.Free();
                GC.KeepAlive(callback);
            }
        }

        private static int OnDeleteFilter(IntPtr item, IntPtr userData)
        {
            try
            {
                var context = (DeleteContext)GCHandle.FromIntPtr(userData).Target;

                using (var wrapper = new AimpPlaylistItemWrapper(AimpComHelper.AddRef(item)))
                {
                    return context.Filter(wrapper, context.Data) ? 1 : 0;
                }
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }

        public AimpActionResult DeleteAll()
        {
            return AimpResult.From(_native.DeleteAll());
        }

        #endregion

        #region Sorting

        public AimpActionResult Sort(PlaylistSort sort)
        {
            return AimpResult.From(_native.Sort((int)sort));
        }

        public AimpActionResult Sort(string template)
        {
            var pointer = AimpString.CreateNative(template ?? string.Empty);

            try
            {
                return AimpResult.From(_native.Sort2(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Sort(
            object customCompareData,
            Func<IAimpPlaylistItem, IAimpPlaylistItem, object, PlaylistSortCompareResult> compareFunc)
        {
            if (compareFunc == null)
            {
                return AimpResult.From(_native.Sort3(IntPtr.Zero, IntPtr.Zero));
            }

            var context = new SortContext { Data = customCompareData, Compare = compareFunc };
            var handle = GCHandle.Alloc(context);

            SortCompareProc callback = OnCompare;

            try
            {
                return AimpResult.From(
                    _native.Sort3(
                        Marshal.GetFunctionPointerForDelegate(callback),
                        GCHandle.ToIntPtr(handle)));
            }
            finally
            {
                handle.Free();
                GC.KeepAlive(callback);
            }
        }

        private static int OnCompare(IntPtr item1, IntPtr item2, IntPtr userData)
        {
            try
            {
                var context = (SortContext)GCHandle.FromIntPtr(userData).Target;

                using (var first = new AimpPlaylistItemWrapper(AimpComHelper.AddRef(item1)))
                using (var second = new AimpPlaylistItemWrapper(AimpComHelper.AddRef(item2)))
                {
                    return (int)context.Compare(first, second, context.Data);
                }
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }

        #endregion

        #region Other commands

        public AimpActionResult BeginUpdate()
        {
            return AimpResult.From(_native.BeginUpdate());
        }

        public AimpActionResult EndUpdate()
        {
            return AimpResult.From(_native.EndUpdate());
        }

        public AimpActionResult Close(PlaylistCloseFlag closeFlag)
        {
            RemoveListener();

            return AimpResult.From(_native.Close((uint)closeFlag));
        }

        public AimpActionResult<IList<string>> GetFiles(PlaylistGetFilesFlag filesFlag)
        {
            var hr = _native.GetFiles((uint)filesFlag, out var pointer);
            if (hr < 0 || pointer == IntPtr.Zero)
            {
                return AimpResult.From<IList<string>>(hr, null);
            }

            var files = new List<string>();

            using (var list = new AimpObjectList(pointer))
            {
                for (var i = 0; i < list.Count; i++)
                {
                    files.Add(list.GetString(i));
                }
            }

            return AimpResult.Ok<IList<string>>(files);
        }

        public AimpActionResult MergeGroup(IAimpPlaylistGroup playlistGroup)
        {
            var pointer = AimpBridgeHelper.GetPointer(playlistGroup, typeof(IAIMPPlaylistGroupNative));

            try
            {
                return AimpResult.From(_native.MergeGroup(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult ReloadFromPreimage()
        {
            return AimpResult.From(_native.ReloadFromPreimage());
        }

        public AimpActionResult ReloadInfo(bool fullReload)
        {
            return AimpResult.From(_native.ReloadInfo(fullReload ? 1u : 0u));
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

        public AimpActionResult<IAimpPlaylistGroup> GetGroup(int index)
        {
            var iid = AimpIids.IAIMPPlaylistGroup;
            var hr = _native.GetGroup(index, ref iid, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpPlaylistGroup>(hr, null)
                : AimpResult.Ok<IAimpPlaylistGroup>(new AimpPlaylistGroupWrapper(pointer));
        }

        public int GetGroupCount()
        {
            return _native.GetGroupCount();
        }

        #endregion

        protected override void OnDispose()
        {
            RemoveListener();

            _properties?.Dispose();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }

            AimpComHelper.Release(_pointer);
        }
    }
}
