using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpPlaylistItem"/> over the native <c>IAIMPPlaylistItem</c>.
    /// </summary>
    internal sealed class AimpPlaylistItemWrapper : AimpObjectWrapper, IAimpPlaylistItem, IAimpNativeObject
    {
        private readonly IntPtr _pointer;
        private readonly IAIMPPlaylistItemNative _native;
        private readonly AimpPropertyBag _properties;

        public AimpPlaylistItemWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPPlaylistItemNative>(ownedPointer);
            _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        public string DisplayText => _properties.GetString(AimpPropId.PlaylistItemDisplayText);

        public IAimpFileInfo FileInfo
        {
            get
            {
                var pointer = _properties.GetObjectPointer(
                    AimpPropId.PlaylistItemFileInfo,
                    AimpIids.IAIMPFileInfo);

                return pointer == IntPtr.Zero ? null : new AimpFileInfoWrapper(pointer);
            }
        }

        public string FileName
        {
            get => _properties.GetString(AimpPropId.PlaylistItemFileName);
            set => _properties.SetString(AimpPropId.PlaylistItemFileName, value);
        }

        public IAimpPlaylistGroup Group
        {
            get
            {
                var pointer = _properties.GetObjectPointer(
                    AimpPropId.PlaylistItemGroup,
                    AimpIids.IAIMPPlaylistGroup);

                return pointer == IntPtr.Zero ? null : new AimpPlaylistGroupWrapper(pointer);
            }
        }

        public int Index
        {
            get => _properties.GetInt32(AimpPropId.PlaylistItemIndex);
            set => _properties.SetInt32(AimpPropId.PlaylistItemIndex, value);
        }

        public double Mark
        {
            get => _properties.GetFloat(AimpPropId.PlaylistItemMark);
            set => _properties.SetFloat(AimpPropId.PlaylistItemMark, value);
        }

        public int PlaybackIndex => _properties.GetInt32(AimpPropId.PlaylistItemPlaybackQueueIndex);

        public bool PlaybackSwitch
        {
            get => _properties.GetBool(AimpPropId.PlaylistItemPlayingSwitch);
            set => _properties.SetBool(AimpPropId.PlaylistItemPlayingSwitch, value);
        }

        public IAimpPlaylist PlayList
        {
            get
            {
                var pointer = _properties.GetObjectPointer(
                    AimpPropId.PlaylistItemPlaylist,
                    AimpIids.IAIMPPlaylist);

                return pointer == IntPtr.Zero ? null : new AimpPlaylistWrapper(pointer);
            }
            set
            {
                var pointer = AimpBridgeHelper.GetPointer(value, typeof(IAIMPPlaylistNative));

                try
                {
                    _properties.SetObject(AimpPropId.PlaylistItemPlaylist, pointer);
                }
                finally
                {
                    AimpComHelper.Release(pointer);
                }
            }
        }

        public bool Selected
        {
            get => _properties.GetBool(AimpPropId.PlaylistItemSelected);
            set => _properties.SetBool(AimpPropId.PlaylistItemSelected, value);
        }

        public AimpActionResult ReloadInfo()
        {
            return AimpResult.From(_native.ReloadInfo());
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