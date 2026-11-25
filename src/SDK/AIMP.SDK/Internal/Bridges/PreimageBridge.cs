using System;
using System.Collections;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.Player;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.PlayList;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpPlaylistPreimage"/> (and its optional ML flavour,
    /// folders flavour and data provider) to the native preimage vtables.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class PreimageBridge :
        IAIMPPlaylistPreimageNative,
        IAIMPMLPlaylistPreimageNative,
        IAIMPPlaylistPreimageFoldersNative,
        IAIMPPlaylistPreimageDataProviderNative,
        ICustomQueryInterface
    {
        private readonly IAimpPlaylistPreimage _preimage;
        private readonly IAimpMusicLibraryPlaylistPreimage _mlPreimage;
        private readonly IAimpPlaylistPreimageFolders _folders;
        private readonly IAimpPlaylistPreimageDataProvider _dataProvider;

        public PreimageBridge(IAimpPlaylistPreimage preimage)
        {
            _preimage = preimage ?? throw new ArgumentNullException(nameof(preimage));
            _mlPreimage = preimage as IAimpMusicLibraryPlaylistPreimage;
            _folders = preimage as IAimpPlaylistPreimageFolders;
            _dataProvider = preimage as IAimpPlaylistPreimageDataProvider;
        }

        public CustomQueryInterfaceResult GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IUnknown ||
                iid == AimpIids.IAIMPPlaylistPreimage ||
                (iid == AimpIids.IAIMPMLPlaylistPreimage && _mlPreimage != null) ||
                (iid == AimpIids.IAIMPPlaylistPreimageDataProvider && _dataProvider != null))
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            return CustomQueryInterfaceResult.Failed;
        }

        #region IAIMPPlaylistPreimage (property list)

        [PreserveSig]
        public void BeginUpdate()
        {
        }

        [PreserveSig]
        public void EndUpdate()
        {
        }

        [PreserveSig]
        public int Reset()
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int GetValueAsFloat(int propertyId, out double value)
        {
            value = 0;
            return Safe.E_NOTIMPL;
        }

        [PreserveSig]
        public int GetValueAsInt32(int propertyId, out int value)
        {
            value = 0;

            switch (propertyId)
            {
                case AimpPropId.PlaylistPreimageAutoSync:
                    value = _preimage.AutoSync ? 1 : 0;
                    return Safe.S_OK;

                case AimpPropId.PlaylistPreimageHasDialog:
                    value = _preimage.HasDialog ? 1 : 0;
                    return Safe.S_OK;

                case AimpPropId.PlaylistPreimageAutoSyncOnStartup:
                    value = _preimage.AutoSyncOnStartup ? 1 : 0;
                    return Safe.S_OK;

                default:
                    return Safe.S_OK;
            }
        }

        [PreserveSig]
        public int GetValueAsInt64(int propertyId, out long value)
        {
            value = 0;
            return Safe.E_NOTIMPL;
        }

        [PreserveSig]
        public int GetValueAsObject(int propertyId, ref Guid iid, out IntPtr value)
        {
            value = IntPtr.Zero;

            switch (propertyId)
            {
                case AimpPropId.PlaylistPreimageFactoryId:
                    value = AimpString.CreateNative(_preimage.FactoryId ?? string.Empty);
                    return Safe.S_OK;

                case AimpPropId.PlaylistPreimageSortTemplate:
                    value = AimpString.CreateNative(_preimage.SortTemplate ?? string.Empty);
                    return Safe.S_OK;

                default:
                    return Safe.S_OK;
            }
        }

        [PreserveSig]
        public int SetValueAsFloat(int propertyId, double value)
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsInt32(int propertyId, int value)
        {
            switch (propertyId)
            {
                case AimpPropId.PlaylistPreimageAutoSync:
                    _preimage.AutoSync = value != 0;
                    return Safe.S_OK;

                case AimpPropId.PlaylistPreimageAutoSyncOnStartup:
                    _preimage.AutoSyncOnStartup = value != 0;
                    return Safe.S_OK;

                default:
                    return Safe.S_OK;
            }
        }

        [PreserveSig]
        public int SetValueAsInt64(int propertyId, long value)
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsObject(int propertyId, IntPtr value)
        {
            return Safe.S_OK;
        }

        #endregion

        #region IAIMPPlaylistPreimage

        [PreserveSig]
        public void PreimageFinalize()
        {
            Safe.Run(() => _preimage.FinalizeObject());
        }

        [PreserveSig]
        public void Initialize(IntPtr listener)
        {
            Safe.Run(() => _preimage.Initialize(new AimpPlaylistPreimageListenerWrapper(listener)));
        }

        [PreserveSig]
        public int ConfigLoad(IntPtr stream)
        {
            return Safe.Run(() =>
            {
                using (var source = new AimpStreamWrapper(stream))
                {
                    return ToHResult(_preimage.ConfigLoad(source));
                }
            });
        }

        [PreserveSig]
        public int ConfigSave(IntPtr stream)
        {
            return Safe.Run(() =>
            {
                using (var source = new AimpStreamWrapper(stream))
                {
                    return ToHResult(_preimage.ConfigSave(source));
                }
            });
        }

        [PreserveSig]
        public int ExecuteDialog(IntPtr ownerHandle)
        {
            return Safe.Run(() => ToHResult(_preimage.ExecuteDialog(ownerHandle)));
        }

        #endregion

        #region IAIMPPlaylistPreimageFolders

        [PreserveSig]
        int IAIMPPlaylistPreimageFoldersNative.ItemsAdd(IntPtr path, int recursive)
        {
            return Safe.Run(() => ToHResult(_folders.ItemsAdd(AimpString.Read(path), recursive != 0)));
        }

        [PreserveSig]
        int IAIMPPlaylistPreimageFoldersNative.ItemsDelete(int index)
        {
            return Safe.Run(() => ToHResult(_folders.ItemsDelete(index)));
        }

        [PreserveSig]
        int IAIMPPlaylistPreimageFoldersNative.ItemsDeleteAll()
        {
            return Safe.Run(() => ToHResult(_folders.ItemsDeleteAll()));
        }

        [PreserveSig]
        int IAIMPPlaylistPreimageFoldersNative.ItemsGet(int index, out IntPtr path, out int recursive)
        {
            var pathPointer = IntPtr.Zero;
            var recursiveValue = 0;

            var hr = Safe.Run(() =>
            {
                var item = _folders.ItemsGet(index);
                if (item.ResultType != ActionResultType.OK)
                {
                    return (int)item.ResultType;
                }

                pathPointer = AimpString.CreateNative(item.Item1 ?? string.Empty);
                recursiveValue = item.Item2 ? 1 : 0;
                return Safe.S_OK;
            });

            path = pathPointer;
            recursive = recursiveValue;
            return hr;
        }

        [PreserveSig]
        int IAIMPPlaylistPreimageFoldersNative.ItemsGetCount()
        {
            return Safe.Run(() => _folders.ItemsGetCount(), 0);
        }

        #endregion

        #region IAIMPMLPlaylistPreimage

        [PreserveSig]
        public int GetFilter(out IntPtr filter)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                if (_mlPreimage == null)
                {
                    return Safe.E_NOTIMPL;
                }

                var value = _mlPreimage.GetFilter();
                if (value.ResultType != ActionResultType.OK || value.Result == null)
                {
                    return (int)value.ResultType;
                }

                result = AimpBridgeHelper.GetPointer(value.Result, typeof(IAIMPMLDataFilterNative));
                return Safe.S_OK;
            });

            filter = result;
            return hr;
        }

        [PreserveSig]
        public int GetStorage(out IntPtr storage)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                if (_mlPreimage == null)
                {
                    return Safe.E_NOTIMPL;
                }

                var value = _mlPreimage.GetStorage();
                if (value.ResultType != ActionResultType.OK || value.Result == null)
                {
                    return (int)value.ResultType;
                }

                result = AimpBridgeHelper.GetPointer(value.Result, typeof(IAIMPMLDataStorageNative));
                return Safe.S_OK;
            });

            storage = result;
            return hr;
        }

        #endregion

        #region IAIMPPlaylistPreimageDataProvider

        [PreserveSig]
        public int GetFiles(IntPtr owner, out IntPtr flags, out IntPtr list)
        {
            var flagPointer = IntPtr.Zero;
            var listPointer = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                if (_dataProvider == null)
                {
                    return Safe.E_NOTIMPL;
                }

                var taskOwner = new AimpTaskOwnerWrapper(owner);
                AimpActionResult<int, IList> result;

                using (taskOwner)
                {
                    result = _dataProvider.GetFiles(taskOwner);
                }

                if (result == null)
                {
                    return Safe.E_FAIL;
                }

                if (result.ResultType != ActionResultType.OK)
                {
                    return (int)result.ResultType;
                }

                flagPointer = Marshal.AllocHGlobal(sizeof(int));
                Marshal.WriteInt32(flagPointer, result.Item1);

                var objects = AimpObjectList.Create();

                try
                {
                    var collection = result.Item2;

                    if (collection != null)
                    {
                        foreach (var item in collection)
                        {
                            if (item is string text)
                            {
                                objects.Add(text);
                            }
                            else if (item is IAimpFileInfo fileInfo)
                            {
                                var pointer = AimpBridgeHelper.GetPointer(
                                    fileInfo,
                                    typeof(IAIMPFileInfoNative));

                                try
                                {
                                    objects.Add(pointer);
                                }
                                finally
                                {
                                    AimpComHelper.Release(pointer);
                                }
                            }
                        }
                    }

                    listPointer = objects.AddRefPointer();
                }
                finally
                {
                    objects.Dispose();
                }

                return Safe.S_OK;
            });

            flags = flagPointer;
            list = listPointer;
            return hr;
        }

        #endregion

        private static int ToHResult(AimpActionResult result)
        {
            return result == null ? Safe.E_FAIL : (int)result.ResultType;
        }
    }
}
