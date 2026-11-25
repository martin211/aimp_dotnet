using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.MusicLibrary;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceMusicLibrary"/>.
    /// </summary>
    internal sealed class AimpMusicLibraryService : AimpObjectWrapper, IAimpServiceMusicLibrary
    {
        private readonly IAIMPServiceMusicLibraryNative _native;

        public AimpMusicLibraryService(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceMusicLibraryNative>(borrowedPointer);
        }

        public bool IsExists => _native != null;

        public AimpActionResult<IAimpDataStorage> GetActiveStorage()
        {
            var iid = AimpIids.IAIMPMLDataStorage;
            return _native == null || _native.GetActiveStorage(ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpDataStorage>()
                : AimpResult.Ok<IAimpDataStorage>(new AimpDataStorageWrapper(pointer));
        }

        public AimpActionResult<IAimpGroupingPresets> GetActiveGroupingPresets()
        {
            return AimpResult.Fail<IAimpGroupingPresets>();
        }

        public AimpActionResult SetActiveStorage(IAimpDataStorage storage)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var native = storage as AimpDataStorageWrapper;
            if (native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = native.NativePointer;
            try
            {
                return AimpResult.From(_native.SetActiveStorage(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult SetActiveStorage(IAimpGroupingPresets preset)
        {
            return AimpResult.Fail();
        }

        public AimpActionResult<IAimpDataStorage> GetStorage(int index)
        {
            var iid = AimpIids.IAIMPMLDataStorage;
            return _native == null || _native.GetStorage(index, ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpDataStorage>()
                : AimpResult.Ok<IAimpDataStorage>(new AimpDataStorageWrapper(pointer));
        }

        public AimpActionResult<IAimpGroupingPresets> GetGroupingPresets(int index)
        {
            return AimpResult.Fail<IAimpGroupingPresets>();
        }

        public AimpActionResult<TAimpDataStorage> GetStorageById<TAimpDataStorage>(string id = null)
            where TAimpDataStorage : IAimpDataStorage
        {
            if (string.IsNullOrEmpty(id))
            {
                var active = GetActiveStorage();
                if (active.ResultType != ActionResultType.OK || active.Result == null)
                {
                    return AimpResult.Fail<TAimpDataStorage>();
                }

                if (active.Result is TAimpDataStorage typed)
                {
                    return AimpResult.Ok(typed);
                }

                if (active.Result is IAimpNativeObject native &&
                    typeof(TAimpDataStorage) == typeof(IAimpLocalDataStorage))
                {
                    return AimpResult.Ok(
                        (TAimpDataStorage)(object)new AimpLocalDataStorageWrapper(native.NativePointer));
                }

                return AimpResult.Fail<TAimpDataStorage>();
            }

            if (_native == null)
            {
                return AimpResult.Fail<TAimpDataStorage>();
            }

            var idPointer = AimpString.CreateNative(id);
            var iid = AimpIids.IAIMPMLDataStorage;

            try
            {
                return _native.GetStorageByID(idPointer, ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
                    ? AimpResult.Fail<TAimpDataStorage>()
                    : AimpResult.Ok((TAimpDataStorage)(object)CreateStorageWrapper<TAimpDataStorage>(pointer));
            }
            finally
            {
                AimpComHelper.Release(idPointer);
            }
        }

        private static IAimpDataStorage CreateStorageWrapper<TAimpDataStorage>(IntPtr pointer)
            where TAimpDataStorage : IAimpDataStorage
        {
            return typeof(TAimpDataStorage) == typeof(IAimpLocalDataStorage)
                ? new AimpLocalDataStorageWrapper(pointer)
                : (IAimpDataStorage)new AimpDataStorageWrapper(pointer);
        }

        public AimpActionResult<IAimpGroupingPresets> GetGroupingPresetsById(string id)
        {
            return AimpResult.Fail<IAimpGroupingPresets>();
        }

        public int GetStorageCount()
        {
            return _native?.GetStorageCount() ?? 0;
        }

        protected override void OnDispose()
        {
            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}