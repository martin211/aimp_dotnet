using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Playlist;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// Native listener that forwards queue notifications to a wrapper.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class AimpPlaylistQueueListenerBridge : IAIMPPlaylistQueueListenerNative
    {
        private readonly AimpPlaylistQueueWrapper _owner;

        public AimpPlaylistQueueListenerBridge(AimpPlaylistQueueWrapper owner)
        {
            _owner = owner ?? throw new ArgumentNullException(nameof(owner));
        }

        [PreserveSig]
        public void ContentChanged()
        {
            Safe.Run(() => _owner.RaiseContentChanged());
        }

        [PreserveSig]
        public void StateChanged()
        {
            Safe.Run(() => _owner.RaiseStateChanged());
        }
    }
}