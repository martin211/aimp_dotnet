using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpPlaylistGroup"/> over the native <c>IAIMPPlaylistGroup</c>.
    /// </summary>
    internal sealed class AimpPlaylistGroupWrapper : AimpObjectWrapper, IAimpPlaylistGroup, IAimpNativeObject
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPPlaylistGroupNative _native;
        private readonly AimpPropertyBag _properties;

        public AimpPlaylistGroupWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPPlaylistGroupNative>(ownedPointer);
            _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        public string Name => _properties.GetString(AimpPropId.PlaylistGroupName);

        public bool Expanded
        {
            get => _properties.GetBool(AimpPropId.PlaylistGroupExpanded);
            set => _properties.SetBool(AimpPropId.PlaylistGroupExpanded, value);
        }

        public double Duration => _properties.GetFloat(AimpPropId.PlaylistGroupDuration);

        public int Index => _properties.GetInt32(AimpPropId.PlaylistGroupIndex);

        public bool Selected
        {
            get => _properties.GetBool(AimpPropId.PlaylistGroupSelected);
            set => _properties.SetBool(AimpPropId.PlaylistGroupSelected, value);
        }

        public int Count => _native.GetItemCount();

        public AimpActionResult<IAimpPlaylistItem> GetItem(int index)
        {
            var iid = AimpIids.IAIMPPlaylistItem;
            var hr = _native.GetItem(index, ref iid, out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpPlaylistItem>(hr, null)
                : AimpResult.Ok<IAimpPlaylistItem>(new AimpPlaylistItemWrapper(pointer));
        }

        protected override void OnDispose()
        {
            _properties.Dispose();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}