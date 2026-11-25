using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.MusicLibrary;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.Objects;
using AIMP.SDK.PlayList;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpPlaylistPreimage"/> over a native preimage.
    /// </summary>
    internal class AimpPlaylistPreimageWrapper :
        AimpObjectWrapper,
        IAimpPlaylistPreimage,
        IAimpMusicLibraryPlaylistPreimage,
        IAimpNativeObject
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPPlaylistPreimageNative _native;
        private readonly IAIMPMLPlaylistPreimageNative _mlNative;
        private readonly AimpPropertyBag _properties;

        public AimpPlaylistPreimageWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPPlaylistPreimageNative>(AimpComHelper.AddRef(ownedPointer));
            _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);

            var mlPointer = AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPMLPlaylistPreimage);

            if (mlPointer != IntPtr.Zero)
            {
                _mlNative = AimpComHelper.Wrap<IAIMPMLPlaylistPreimageNative>(mlPointer);
            }
        }

        /// <summary>
        /// Creates the most specific wrapper for the given preimage pointer.
        /// </summary>
        public static AimpPlaylistPreimageWrapper Wrap(IntPtr ownedPointer)
        {
            if (ownedPointer == IntPtr.Zero)
            {
                return null;
            }

            var folders = AimpComHelper.QueryInterface(ownedPointer, AimpIids.IAIMPPlaylistPreimageFolders);

            if (folders != IntPtr.Zero)
            {
                AimpComHelper.Release(folders);
                return new AimpPlaylistPreimageFoldersWrapper(ownedPointer);
            }

            return new AimpPlaylistPreimageWrapper(ownedPointer);
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        protected IntPtr Pointer => _pointer;

        protected AimpPropertyBag Properties => _properties;

        public string FactoryId => _properties.GetString(AimpPropId.PlaylistPreimageFactoryId);

        public bool AutoSync
        {
            get => _properties.GetBool(AimpPropId.PlaylistPreimageAutoSync);
            set => _properties.SetBool(AimpPropId.PlaylistPreimageAutoSync, value);
        }

        public bool AutoSyncOnStartup
        {
            get => _properties.GetBool(AimpPropId.PlaylistPreimageAutoSyncOnStartup);
            set => _properties.SetBool(AimpPropId.PlaylistPreimageAutoSyncOnStartup, value);
        }

        public bool HasDialog => _properties.GetBool(AimpPropId.PlaylistPreimageHasDialog);

        public string SortTemplate => _properties.GetString(AimpPropId.PlaylistPreimageSortTemplate);

        public AimpActionResult ConfigLoad(IAimpStream stream)
        {
            var pointer = AimpBridgeHelper.GetStreamPointer(stream);

            try
            {
                return AimpResult.From(_native.ConfigLoad(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult ConfigSave(IAimpStream stream)
        {
            var pointer = AimpBridgeHelper.GetStreamPointer(stream);

            try
            {
                return AimpResult.From(_native.ConfigSave(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult ExecuteDialog(IntPtr ownerHandle)
        {
            return AimpResult.From(_native.ExecuteDialog(ownerHandle));
        }

        public void Initialize(IAimpPlaylistPreimageListener listener)
        {
            var pointer = (listener as AimpPlaylistPreimageListenerWrapper)?.NativePointer ?? IntPtr.Zero;

            try
            {
                _native.Initialize(pointer);
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public void FinalizeObject()
        {
            _native.PreimageFinalize();
        }

        public AimpActionResult<IAimpDataFilter> GetFilter()
        {
            if (_mlNative == null)
            {
                return AimpResult.Fail<IAimpDataFilter>();
            }

            var hr = _mlNative.GetFilter(out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpDataFilter>(hr, null)
                : AimpResult.Ok<IAimpDataFilter>(new AimpDataFilterWrapper(pointer));
        }

        public AimpActionResult<IAimpDataStorage> GetStorage()
        {
            if (_mlNative == null)
            {
                return AimpResult.Fail<IAimpDataStorage>();
            }

            var hr = _mlNative.GetStorage(out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpDataStorage>(hr, null)
                : AimpResult.Ok<IAimpDataStorage>(new AimpDataStorageWrapper(pointer));
        }

        protected override void OnDispose()
        {
            _properties.Dispose();

            if (_mlNative != null)
            {
                Marshal.FinalReleaseComObject(_mlNative);
            }

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }

            AimpComHelper.Release(_pointer);
        }
    }
}