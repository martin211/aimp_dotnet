using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Playlist;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// Native listener that forwards <c>IAIMPPlaylist</c> notifications to a wrapper.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class AimpPlaylistListenerBridge :
        IAIMPPlaylistListenerNative,
        IAIMPPlaylistListener2Native,
        ICustomQueryInterface
    {
        private readonly AimpPlaylistWrapper _owner;

        public AimpPlaylistListenerBridge(AimpPlaylistWrapper owner)
        {
            _owner = owner ?? throw new ArgumentNullException(nameof(owner));
        }

        public CustomQueryInterfaceResult GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IUnknown ||
                iid == AimpIids.IAIMPPlaylistListener ||
                iid == AimpIids.IAIMPPlaylistListener2)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            return CustomQueryInterfaceResult.Failed;
        }

        [PreserveSig]
        public void Activated()
        {
            Safe.Run(() => _owner.RaiseActivated());
        }

        [PreserveSig]
        public void Changed(uint flags)
        {
            Safe.Run(() => _owner.RaiseChanged(flags));
        }

        [PreserveSig]
        public void Removed()
        {
            Safe.Run(() => _owner.RaiseRemoved());
        }

        [PreserveSig]
        public void ScanningBegin()
        {
            Safe.Run(() => _owner.RaiseScanningBegin());
        }

        [PreserveSig]
        public void ScanningProgress(double progress)
        {
            Safe.Run(() => _owner.RaiseScanningProgress(progress));
        }

        [PreserveSig]
        public void ScanningEnd(int hasChanges, int canceled)
        {
            Safe.Run(() => _owner.RaiseScanningEnd(hasChanges != 0, canceled != 0));
        }
    }
}