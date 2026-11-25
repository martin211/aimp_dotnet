using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Native.Player;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Player;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// v1 <see cref="IAimpServicePlayer"/>.
    /// </summary>
    internal sealed class AimpPlayerService : AimpObjectWrapper, IAimpServicePlayer
    {
        private readonly IAIMPServicePlayer2Native _native;
        private readonly AimpPropertyBag _properties;

        public AimpPlayerService(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServicePlayer2Native>(borrowedPointer);
            _properties = AimpPropertyBag.FromOwned(
                AimpComHelper.QueryInterface(borrowedPointer, AimpIids.IAIMPPropertyList));
        }

        public bool IsExists => _native != null;

        public AimpPlayerState State =>
            _native == null ? AimpPlayerState.Stopped : (AimpPlayerState)_native.GetState();

        public double Duration =>
            _native != null && _native.GetDuration(out var value) >= 0 ? value : 0d;

        public double Position
        {
            get => _native != null && _native.GetPosition(out var value) >= 0 ? value : 0d;
            set => _native?.SetPosition(value);
        }

        public float Volume
        {
            get => _native != null && _native.GetVolume(out var value) >= 0 ? value : 0f;
            set => _native?.SetVolume(value);
        }

        public bool IsMute
        {
            get => _native != null && _native.GetMute(out var value) >= 0 && value != 0;
            set => _native?.SetMute(value ? 1 : 0);
        }

        public IAimpFileInfo CurrentFileInfo
        {
            get
            {
                if (_native == null || _native.GetInfo(out var pointer) < 0 || pointer == IntPtr.Zero)
                {
                    return null;
                }

                return new AimpFileInfoWrapper(pointer);
            }
        }

        public IAimpPlaylistItem CurrentPlaylistItem
        {
            get
            {
                if (_native == null || _native.GetPlaylistItem(out var pointer) < 0 || pointer == IntPtr.Zero)
                {
                    return null;
                }

                return new AimpPlaylistItemWrapper(pointer);
            }
        }

        public ActionOnTrackEnd ActionOnEndOfTrack
        {
            get => _properties == null
                ? ActionOnTrackEnd.None
                : (ActionOnTrackEnd)_properties.GetInt32(AimpPropId.PlayerStopAfterTrack);
            set => _properties?.SetInt32(AimpPropId.PlayerStopAfterTrack, (int)value);
        }

        public bool AutoJumpToNextTrack
        {
            get => _properties != null && _properties.GetBool(AimpPropId.PlayerAutoJumpToNextTrack);
            set => _properties?.SetBool(AimpPropId.PlayerAutoJumpToNextTrack, value);
        }

        public bool AutoSwitching
        {
            get => _properties != null && _properties.GetBool(AimpPropId.PlayerAutoSwitching);
            set => _properties?.SetBool(AimpPropId.PlayerAutoSwitching, value);
        }

        public int AutoSwitchingPauseBetweenTracks
        {
            get => _properties?.GetInt32(AimpPropId.PlayerAutoSwitchingPauseBetweenTracks) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerAutoSwitchingPauseBetweenTracks, value);
        }

        public int AutoSwitchingCrossFade
        {
            get => _properties?.GetInt32(AimpPropId.PlayerAutoSwitchingCrossfade) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerAutoSwitchingCrossfade, value);
        }

        public int AutoSwitchingFadeIn
        {
            get => _properties?.GetInt32(AimpPropId.PlayerAutoSwitchingFadeIn) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerAutoSwitchingFadeIn, value);
        }

        public int AutoSwitchingFadeOut
        {
            get => _properties?.GetInt32(AimpPropId.PlayerAutoSwitchingFadeOut) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerAutoSwitchingFadeOut, value);
        }

        public bool ManualSwitching
        {
            get => _properties != null && _properties.GetBool(AimpPropId.PlayerManualSwitching);
            set => _properties?.SetBool(AimpPropId.PlayerManualSwitching, value);
        }

        public int ManualSwitchingCrossFade
        {
            get => _properties?.GetInt32(AimpPropId.PlayerManualSwitchingCrossfade) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerManualSwitchingCrossfade, value);
        }

        public int ManualSwitchingFadeIn
        {
            get => _properties?.GetInt32(AimpPropId.PlayerManualSwitchingFadeIn) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerManualSwitchingFadeIn, value);
        }

        public int ManualSwitchingFadeOut
        {
            get => _properties?.GetInt32(AimpPropId.PlayerManualSwitchingFadeOut) ?? 0;
            set => _properties?.SetInt32(AimpPropId.PlayerManualSwitchingFadeOut, value);
        }

        public AimpActionResult Play(IAimpPlaybackQueueItem queueItem)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = AimpBridgeHelper.GetPointer(queueItem, typeof(IAIMPPropertyListNative));

            try
            {
                return AimpResult.From(_native.Play(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Play(IAimpPlaylistItem playlistItem)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = AimpBridgeHelper.GetPointer(playlistItem, typeof(IAIMPPlaylistItemNative));

            try
            {
                return AimpResult.From(_native.Play2(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Play(IAimpPlaylist playList)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = AimpBridgeHelper.GetPointer(playList, typeof(IAIMPPlaylistNative));

            try
            {
                return AimpResult.From(_native.Play3(pointer));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Play(string fileUri, PlayFlags flags)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var text = AimpString.CreateNative(fileUri ?? string.Empty);

            try
            {
                return AimpResult.From(_native.Play4(text, (uint)flags));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult Play(IAimpPlaybackQueueItem item, int offset, PlayFlags flags)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = AimpBridgeHelper.GetPointer(item, typeof(IAIMPPropertyListNative));

            try
            {
                return AimpResult.From(_native.PlayWithOffset(pointer, offset, (uint)flags));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Play(IAimpPlaylistItem item, int offset, PlayFlags flags)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var pointer = AimpBridgeHelper.GetPointer(item, typeof(IAIMPPlaylistItemNative));

            try
            {
                return AimpResult.From(_native.Play2WithOffset(pointer, offset, (uint)flags));
            }
            finally
            {
                AimpComHelper.Release(pointer);
            }
        }

        public AimpActionResult Play(string fileUri, int offset, PlayFlags flags)
        {
            if (_native == null)
            {
                return AimpResult.Fail();
            }

            var text = AimpString.CreateNative(fileUri ?? string.Empty);

            try
            {
                return AimpResult.From(_native.Play4WithOffset(text, offset, (uint)flags));
            }
            finally
            {
                AimpComHelper.Release(text);
            }
        }

        public AimpActionResult GoToNext() => _native == null ? AimpResult.Fail() : AimpResult.From(_native.GoToNext());

        public AimpActionResult GoToPrev() => _native == null ? AimpResult.Fail() : AimpResult.From(_native.GoToPrev());

        public AimpActionResult Pause() => _native == null ? AimpResult.Fail() : AimpResult.From(_native.Pause());

        public AimpActionResult Resume() => _native == null ? AimpResult.Fail() : AimpResult.From(_native.Resume());

        public AimpActionResult Stop() => _native == null ? AimpResult.Fail() : AimpResult.From(_native.Stop());

        public AimpActionResult StopAfterTrack() =>
            _native == null ? AimpResult.Fail() : AimpResult.From(_native.StopAfterTrack());

        protected override void OnDispose()
        {
            _properties?.Dispose();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }
        }
    }
}