using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary;
using AIMP.SDK.MusicLibrary.DataStorage;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.Internal.Runtime.MusicLibrary
{
    /// <summary>
    /// v1 <see cref="IAimpGroupingPresets"/> over the native collection.
    /// </summary>
    internal sealed class AimpGroupingPresetsWrapper : AimpObjectWrapper, IAimpGroupingPresets
    {
        private readonly IAIMPMLGroupingPresetsNative _native;
        private readonly List<MlSortItemBridge> _sortItems = new List<MlSortItemBridge>();

        public AimpGroupingPresetsWrapper(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPMLGroupingPresetsNative>(borrowedPointer);
        }

        public void BeginUpdate()
        {
            _native.BeginUpdate();
        }

        public void EndUpdate()
        {
            _native.EndUpdate();
        }

        public AimpActionResult<IAimpGroupingPreset> Add(string id, string name, IAimpGroupingTreeDataProvider provider)
        {
            var idPointer = AimpString.CreateNative(id);
            var namePointer = AimpString.CreateNative(name);

            try
            {
                var bridge = new MlGroupingTreeProviderBridge(provider);
                var providerPointer = AimpComHelper.GetPointer(
                    bridge,
                    typeof(IAIMPMLGroupingTreeDataProvider2Native));

                var hr = _native.Add(idPointer, namePointer, 0, providerPointer, out var preset);
                return hr < 0 || preset == IntPtr.Zero
                    ? AimpResult.Fail<IAimpGroupingPreset>()
                    : AimpResult.Ok<IAimpGroupingPreset>(new AimpGroupingPresetStandardWrapper(preset));
            }
            finally
            {
                AimpComHelper.Release(idPointer);
                AimpComHelper.Release(namePointer);
            }
        }

        public AimpActionResult<IAimpGroupingPresetStandard> Add(string id, string name,
            IList<IAimpSortItem> fieldNames)
        {
            var idPointer = AimpString.CreateNative(id);
            var namePointer = AimpString.CreateNative(name);

            using (var fields = AimpObjectList.Create())
            {
                if (fieldNames != null)
                {
                    foreach (var fieldName in fieldNames)
                    {
                        if (fieldName == null)
                        {
                            continue;
                        }

                        var bridge = new MlSortItemBridge(fieldName);
                        var pointer = AimpComHelper.GetPointer(
                            bridge,
                            typeof(IAIMPMLSortDirectionNative));

                        fields.Add(pointer);
                        AimpComHelper.Release(pointer);
                        _sortItems.Add(bridge);
                    }
                }

                try
                {
                    var hr = _native.Add2(idPointer, namePointer, 0, fields.Pointer, out var preset);
                    return hr < 0 || preset == IntPtr.Zero
                        ? AimpResult.Fail<IAimpGroupingPresetStandard>()
                        : AimpResult.Ok<IAimpGroupingPresetStandard>(new AimpGroupingPresetStandardWrapper(preset));
                }
                finally
                {
                    AimpComHelper.Release(idPointer);
                    AimpComHelper.Release(namePointer);
                }
            }
        }

        /// <summary>
        /// v1 overload: a bare field name list, direction defaults to undefined.
        /// </summary>
        public AimpActionResult<IAimpGroupingPresetStandard> Add(string id, string name, IList<string> fieldNames)
        {
            var items = new List<IAimpSortItem>();
            if (fieldNames != null)
            {
                foreach (var fieldName in fieldNames)
                {
                    if (fieldName != null)
                    {
                        items.Add(new AimpSortItemValue(fieldName));
                    }
                }
            }

            return Add(id, name, items);
        }

        public AimpActionResult<IAimpGroupingPresetStandard> Add(string id, string name, string fieldName)
        {
            var idPointer = AimpString.CreateNative(id);
            var namePointer = AimpString.CreateNative(name);
            var fieldPointer = AimpString.CreateNative(fieldName);

            try
            {
                var hr = _native.Add3(idPointer, namePointer, 0, fieldPointer, out var preset);
                return hr < 0 || preset == IntPtr.Zero
                    ? AimpResult.Fail<IAimpGroupingPresetStandard>()
                    : AimpResult.Ok<IAimpGroupingPresetStandard>(new AimpGroupingPresetStandardWrapper(preset));
            }
            finally
            {
                AimpComHelper.Release(idPointer);
                AimpComHelper.Release(namePointer);
                AimpComHelper.Release(fieldPointer);
            }
        }

        public AimpActionResult Delete(int index)
        {
            return AimpResult.From(_native.Delete(index));
        }

        public AimpActionResult<TAimpGroupingPreset> Get<TAimpGroupingPreset>(int index)
            where TAimpGroupingPreset : IAimpGroupingPreset
        {
            var iid = GroupingPresetIdOf<TAimpGroupingPreset>();
            return _native.Get(index, ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
                ? AimpResult.Fail<TAimpGroupingPreset>()
                : AimpResult.Ok((TAimpGroupingPreset)CreatePreset<TAimpGroupingPreset>(pointer));
        }

        public AimpActionResult<TAimpGroupingPreset> GetById<TAimpGroupingPreset>(string id)
            where TAimpGroupingPreset : IAimpGroupingPreset
        {
            var idPointer = AimpString.CreateNative(id);

            try
            {
                var iid = GroupingPresetIdOf<TAimpGroupingPreset>();
                return _native.GetByID(idPointer, ref iid, out var pointer) < 0 || pointer == IntPtr.Zero
                    ? AimpResult.Fail<TAimpGroupingPreset>()
                    : AimpResult.Ok((TAimpGroupingPreset)CreatePreset<TAimpGroupingPreset>(pointer));
            }
            finally
            {
                AimpComHelper.Release(idPointer);
            }
        }

        public int GetCount()
        {
            return _native.GetCount();
        }

        private static Guid GroupingPresetIdOf<TAimpGroupingPreset>()
            where TAimpGroupingPreset : IAimpGroupingPreset
        {
            return typeof(IAimpGroupingPresetStandard).IsAssignableFrom(typeof(TAimpGroupingPreset))
                ? AimpIids.IAIMPMLGroupingPresetStandard
                : AimpIids.IAIMPMLGroupingPreset;
        }

        private static object CreatePreset<TAimpGroupingPreset>(IntPtr pointer)
            where TAimpGroupingPreset : IAimpGroupingPreset
        {
            return typeof(IAimpGroupingPresetStandard).IsAssignableFrom(typeof(TAimpGroupingPreset))
                ? new AimpGroupingPresetStandardWrapper(pointer)
                : (object)new AimpGroupingPresetWrapper(pointer);
        }

        protected override void OnDispose()
        {
            foreach (var item in _sortItems)
            {
                item.Dispose();
            }

            _sortItems.Clear();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}