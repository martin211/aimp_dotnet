using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.MusicLibrary;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Extension;
using AIMP.SDK.MusicLibrary.Extension.Command;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpExtensionDataStorage"/> (and its optional data
    /// providers, commands and grouping tree provider) to the native media
    /// library interfaces.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class MlStorageBridge :
        IAIMPMLExtensionDataStorageNative,
        IAIMPMLDataProviderNative,
        IAIMPMLDataProvider2Native,
        IAIMPMLDataStorageCommandAddFilesNative,
        IAIMPMLDataStorageCommandAddFilesDialogNative,
        IAIMPMLDataStorageCommandDeleteFilesNative,
        IAIMPMLDataStorageCommandDeleteFiles2Native,
        IAIMPMLDataStorageCommandDropDataNative,
        IAIMPMLDataStorageCommandReloadTagsNative,
        IAIMPMLDataStorageCommandReportDialogNative,
        IAIMPMLDataStorageCommandUserMarkNative,
        ICustomQueryInterface
    {
        private readonly IAimpExtensionDataStorage _storage;
        private readonly IAimpDataProvider _provider;
        private readonly IAimpDataProvider2 _provider2;
        private readonly IAimpDataStorageCommandAddFiles _addFiles;
        private readonly IAimpDataStorageCommandAddFilesDialog _addFilesDialog;
        private readonly IAimpDataStorageCommandDeleteFiles _deleteFiles;
        private readonly IAimpDataStorageCommandDeleteFiles2 _deleteFiles2;
        private readonly IAimpDataStorageCommandDropData _dropData;
        private readonly IAimpDataStorageCommandReloadTags _reloadTags;
        private readonly IAimpDataStorageCommandReportDialog _reportDialog;
        private readonly IAimpDataStorageCommandUserMark _userMark;
        private readonly IAimpGroupingTreeDataProvider _groupingTree;

        private IntPtr _groupingPreset;
        private AimpDataStorageManagerWrapper _storageManager;

        public MlStorageBridge(IAimpExtensionDataStorage storage)
        {
            _storage = storage ?? throw new ArgumentNullException(nameof(storage));
            _provider = storage as IAimpDataProvider;
            _provider2 = storage as IAimpDataProvider2;
            _addFiles = storage as IAimpDataStorageCommandAddFiles;
            _addFilesDialog = storage as IAimpDataStorageCommandAddFilesDialog;
            _deleteFiles = storage as IAimpDataStorageCommandDeleteFiles;
            _deleteFiles2 = storage as IAimpDataStorageCommandDeleteFiles2;
            _dropData = storage as IAimpDataStorageCommandDropData;
            _reloadTags = storage as IAimpDataStorageCommandReloadTags;
            _reportDialog = storage as IAimpDataStorageCommandReportDialog;
            _userMark = storage as IAimpDataStorageCommandUserMark;
            _groupingTree = storage as IAimpGroupingTreeDataProvider;
        }

        public CustomQueryInterfaceResult GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IUnknown || iid == AimpIids.IAIMPMLExtensionDataStorage)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataProvider && _provider != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataProvider2 && _provider2 != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandAddFiles && _addFiles != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandAddFilesDialog && _addFilesDialog != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandDeleteFiles && _deleteFiles != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandDeleteFiles2 && _deleteFiles2 != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandDropData && _dropData != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandReloadTags && _reloadTags != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandReportDialog && _reportDialog != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPMLDataStorageCommandUserMark && _userMark != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (_groupingTree != null)
            {
                var provider = new MlGroupingTreeProviderBridge(_groupingTree);

                ppv = AimpComHelper.GetPointer(provider, typeof(IAIMPMLGroupingTreeDataProvider2Native));
                return CustomQueryInterfaceResult.Handled;
            }

            return CustomQueryInterfaceResult.Failed;
        }

        #region Property list

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
                case AimpMlPropId.DataStorageCapabilities:
                    value = (int)_storage.Capabilities;
                    return Safe.S_OK;

                default:
                    return Safe.E_NOTIMPL;
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
                case AimpMlPropId.DataStorageId:
                    value = AimpString.CreateNative(_storage.Id ?? string.Empty);
                    return value == IntPtr.Zero ? Safe.E_FAIL : Safe.S_OK;

                case AimpMlPropId.DataStorageCaption:
                    value = AimpString.CreateNative(_storage.Caption ?? string.Empty);
                    return value == IntPtr.Zero ? Safe.E_FAIL : Safe.S_OK;

                case AimpMlPropId.DataStorageGroupingPreset:
                    if (_groupingPreset == IntPtr.Zero)
                    {
                        return Safe.E_POINTER;
                    }

                    value = AimpComHelper.AddRef(_groupingPreset);
                    return Safe.S_OK;

                default:
                    return Safe.E_NOTIMPL;
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
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsInt64(int propertyId, long value)
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsObject(int propertyId, IntPtr value)
        {
            if (propertyId == AimpMlPropId.DataStorageGroupingPreset)
            {
                if (_groupingPreset != IntPtr.Zero)
                {
                    AimpComHelper.Release(_groupingPreset);
                }

                _groupingPreset = AimpComHelper.AddRef(value);
            }

            return Safe.S_OK;
        }

        #endregion

        #region Storage extension

        [PreserveSig]
        public void StorageFinalize()
        {
            Safe.Run(() =>
            {
                _storage.Terminate();

                if (_storageManager != null)
                {
                    _storageManager.Dispose();
                    _storageManager = null;
                }
            });
        }

        [PreserveSig]
        public void Initialize(IntPtr manager)
        {
            Safe.Run(() =>
            {
                // The wrapper lives as long as the storage: the plugin may keep
                // a reference to the manager and call Changed() later.
                _storageManager = new AimpDataStorageManagerWrapper(manager);
                _storage.Initialize(_storageManager);
            });
        }

        [PreserveSig]
        public int ConfigLoad(IntPtr config, IntPtr section)
        {
            return Safe.Run(() =>
            {
                using (var aimpConfig = new AimpConfigWrapper(config))
                {
                    return ToHResult(_storage.ConfigLoad(aimpConfig, AimpString.Read(section)));
                }
            });
        }

        [PreserveSig]
        public int ConfigSave(IntPtr config, IntPtr section)
        {
            return Safe.Run(() =>
            {
                using (var aimpConfig = new AimpConfigWrapper(config))
                {
                    return ToHResult(_storage.ConfigSave(aimpConfig, AimpString.Read(section)));
                }
            });
        }

        [PreserveSig]
        public int GetFields(int schema, out IntPtr list)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var fields = _storage.GetFields((SchemaType)schema);
                if (fields.ResultType != ActionResultType.OK)
                {
                    return (int)fields.ResultType;
                }

                result = AimpMlRuntime.CreateFieldList(fields.Result);
                return Safe.S_OK;
            });

            list = result;
            return hr;
        }

        [PreserveSig]
        public int GetGroupingPresets(int schema, IntPtr presets)
        {
            return Safe.Run(() =>
            {
                using (var collection = new AimpGroupingPresetsWrapper(presets))
                {
                    return ToHResult(
                        _storage.GetGroupingPresets((GroupingPresetsSchemaType)schema, collection));
                }
            });
        }

        [PreserveSig]
        public void FlushCache(int reserved)
        {
            Safe.Run(() => _storage.FlushCache());
        }

        #endregion

        #region Data providers

        [PreserveSig]
        int IAIMPMLDataProviderNative.GetData(IntPtr fields, IntPtr filter, out IntPtr data)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                using (var dataFilter = new AimpDataFilterWrapper(AimpComHelper.AddRef(filter)))
                {
                    var value = _provider.GetData(AimpMlRuntime.ReadFieldNames(fields), dataFilter);
                    if (value.ResultType != ActionResultType.OK)
                    {
                        return (int)value.ResultType;
                    }

                    result = ToNativeData(value.Result);
                    return Safe.S_OK;
                }
            });

            data = result;
            return hr;
        }

        [PreserveSig]
        int IAIMPMLDataProvider2Native.GetData(
            IntPtr fields,
            IntPtr filter,
            IntPtr reserved,
            ref IntPtr pageId,
            out IntPtr data)
        {
            var result = IntPtr.Zero;
            var outgoingPage = IntPtr.Zero;
            var incomingPage = pageId;

            var hr = Safe.Run(() =>
            {
                var page = incomingPage == IntPtr.Zero ? null : AimpString.Read(incomingPage);

                using (var dataFilter = new AimpDataFilterWrapper(AimpComHelper.AddRef(filter)))
                {
                    var paged = _provider2.GetData(
                        AimpMlRuntime.ReadFieldNames(fields),
                        dataFilter,
                        page);

                    if (paged.ResultType != ActionResultType.OK)
                    {
                        return (int)paged.ResultType;
                    }

                    var value = paged.Result;
                    if (value == null)
                    {
                        return Safe.S_OK;
                    }

                    outgoingPage = string.IsNullOrEmpty(value.PageId)
                        ? IntPtr.Zero
                        : AimpString.CreateNative(value.PageId);

                    result = string.IsNullOrEmpty(value.NoData)
                        ? ToNativeData(value.Data)
                        : AimpString.CreateNative(value.NoData);

                    return Safe.S_OK;
                }
            });

            pageId = outgoingPage;
            data = result;
            return hr;
        }

        #endregion

        #region Commands

        [PreserveSig]
        int IAIMPMLDataStorageCommandAddFilesNative.Add(IntPtr files)
        {
            return Safe.Run(() =>
            {
                var items = new List<string>();

                using (var list = new AimpObjectList(AimpComHelper.AddRef(files)))
                {
                    for (var i = 0; i < list.Count; i++)
                    {
                        items.Add(list.GetString(i));
                    }
                }

                return ToHResult(_addFiles.Add(items));
            });
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandAddFilesDialogNative.Execute(IntPtr ownerHandle)
        {
            return Safe.Run(() => ToHResult(_addFilesDialog.Execute(ownerHandle)));
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandDeleteFilesNative.CanDelete(int physically)
        {
            return Safe.Run(() => _deleteFiles.CanDelete(physically != 0) ? 1 : 0, 0);
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandDeleteFilesNative.Delete(IntPtr files, int physically)
        {
            return Safe.Run(() =>
            {
                using (var list = new AimpFileListWrapper(AimpComHelper.AddRef(files)))
                {
                    return ToHResult(_deleteFiles.Delete(list, physically != 0));
                }
            });
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandDeleteFiles2Native.CanDelete(int physically)
        {
            return ((IAIMPMLDataStorageCommandDeleteFilesNative)this).CanDelete(physically);
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandDeleteFiles2Native.Delete(IntPtr files, int physically)
        {
            return ((IAIMPMLDataStorageCommandDeleteFilesNative)this).Delete(files, physically);
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandDeleteFiles2Native.Delete2(IntPtr filter, int physically)
        {
            return Safe.Run(() =>
            {
                using (var dataFilter = new AimpDataFilterWrapper(AimpComHelper.AddRef(filter)))
                {
                    return ToHResult(_deleteFiles2.Delete2(dataFilter, physically != 0));
                }
            });
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandDropDataNative.DropData()
        {
            return Safe.Run(() => ToHResult(_dropData.DropData()));
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandReloadTagsNative.ReloadTags(IntPtr files)
        {
            return Safe.Run(() =>
            {
                using (var list = new AimpFileListWrapper(AimpComHelper.AddRef(files)))
                {
                    return ToHResult(_reloadTags.ReloadTags(list));
                }
            });
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandReportDialogNative.Execute(IntPtr ownerHandle)
        {
            return Safe.Run(() => ToHResult(_reportDialog.Execute(ownerHandle)));
        }

        [PreserveSig]
        int IAIMPMLDataStorageCommandUserMarkNative.SetMark(IntPtr id, double value)
        {
            return Safe.Run(() => ToHResult(_userMark.SetMark(AimpVariant.Read(id), value)));
        }

        #endregion

        #region Helpers

        internal static IntPtr ToNativeData(object data)
        {
            if (data is IAimpDataProviderSelection selection)
            {
                return AimpComHelper.GetPointer(
                    new MlDataProviderSelectionBridge(selection),
                    typeof(IAIMPMLDataProviderSelectionNative));
            }

            return AimpMlRuntime.ToNativeValue(data);
        }

        private static int ToHResult(AimpActionResult result)
        {
            return result == null ? Safe.E_FAIL : (int)result.ResultType;
        }

        #endregion
    }
}
