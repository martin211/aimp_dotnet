using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataFilter;
using AIMP.SDK.MusicLibrary.Presets;

namespace AIMP.Internal.Runtime.MusicLibrary
{
    /// <summary>
    /// v1 <see cref="IAimpGroupingPresetStandard"/> over the native preset.
    /// </summary>
    internal sealed class AimpGroupingPresetStandardWrapper : AimpGroupingPresetWrapper, IAimpGroupingPresetStandard
    {
        private readonly IntPtr _pointer;

        public AimpGroupingPresetStandardWrapper(IntPtr ownedPointer)
            : base(ownedPointer)
        {
            _pointer = ownedPointer;
        }

        public IAimpObjectList<string> Fields
        {
            get
            {
                var pointer = GetObjectPointer(
                    AimpMlPropId.GroupingPresetStandardFields,
                    AimpIids.IAIMPObjectList);

                return pointer == IntPtr.Zero
                    ? null
                    : new AimpStringList(new AimpObjectList(pointer));
            }
            set
            {
                var native = value as IAimpNativeObject;
                SetObject(AimpMlPropId.GroupingPresetStandardFields, native?.NativePointer ?? IntPtr.Zero);
            }
        }

        public AimpActionResult<IAimpDataFilterGroup> GetFilter()
        {
            var standard = AimpComHelper.QueryInterface(_pointer, AimpIids.IAIMPMLGroupingPresetStandard);
            if (standard == IntPtr.Zero)
            {
                return AimpResult.Fail<IAimpDataFilterGroup>();
            }

            try
            {
                var native = AimpComHelper.Wrap<IAIMPMLGroupingPresetStandardNative>(standard);
                try
                {
                    return native.GetFilter(out var filter) < 0 || filter == IntPtr.Zero
                        ? AimpResult.Fail<IAimpDataFilterGroup>()
                        : AimpResult.Ok<IAimpDataFilterGroup>(new AimpDataFilterGroupWrapper(filter));
                }
                finally
                {
                    Marshal.FinalReleaseComObject(native);
                }
            }
            catch (InvalidCastException)
            {
                return AimpResult.Fail<IAimpDataFilterGroup>();
            }
        }
    }
}