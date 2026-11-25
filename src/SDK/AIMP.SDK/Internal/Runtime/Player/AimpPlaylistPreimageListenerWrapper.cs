using System;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.PlayList;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// Managed listener handed to a plugin together with a preimage.
    /// </summary>
    internal sealed class AimpPlaylistPreimageListenerWrapper :
        AimpObjectWrapper,
        IAimpPlaylistPreimageListener,
        IAimpNativeObject
    {
        private readonly IntPtr _pointer;
        private AimpPlaylistPreimageListenerHandler _dataChanged;
        private AimpPlaylistPreimageListenerHandler _settingsChanged;

        public AimpPlaylistPreimageListenerWrapper(IntPtr borrowedPointer)
        {
            _pointer = AimpComHelper.AddRef(borrowedPointer);
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        public event AimpPlaylistPreimageListenerHandler DataChanged
        {
            add => _dataChanged += value;
            remove => _dataChanged -= value;
        }

        public event AimpPlaylistPreimageListenerHandler SettingsChanged
        {
            add => _settingsChanged += value;
            remove => _settingsChanged -= value;
        }

        internal void RaiseDataChanged()
        {
            _dataChanged?.Invoke();
        }

        internal void RaiseSettingsChanged()
        {
            _settingsChanged?.Invoke();
        }

        protected override void OnDispose()
        {
            AimpComHelper.Release(_pointer);
        }
    }
}