using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Playlist;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.PlayList.Extensions;
using AIMP.SDK.PlayList.Objects;

namespace AIMP.Internal.Runtime.Player
{
    /// <summary>
    /// Managed wrapper over a native preimage factory.
    /// </summary>
    internal sealed class AimpPlaylistPreimageFactoryWrapper :
        AimpObjectWrapper,
        IAimpExtensionPlaylistPreimageFactory
    {
        private readonly IAIMPExtensionPlaylistPreimageFactoryNative _native;

        public AimpPlaylistPreimageFactoryWrapper(IntPtr ownedPointer)
        {
            _native = AimpComHelper.Wrap<IAIMPExtensionPlaylistPreimageFactoryNative>(ownedPointer);
        }

        public AimpActionResult<IAimpPlaylistPreimage> CreatePreimage()
        {
            var hr = _native.CreatePreimage(out var pointer);

            return hr < 0 || pointer == IntPtr.Zero
                ? AimpResult.From<IAimpPlaylistPreimage>(hr, null)
                : AimpResult.Ok<IAimpPlaylistPreimage>(AimpPlaylistPreimageWrapper.Wrap(pointer));
        }

        public AimpActionResult<string> GetId()
        {
            var hr = _native.GetID(out var pointer);

            return hr < 0
                ? AimpResult.From<string>(hr, null)
                : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        public AimpActionResult<string> GetName()
        {
            var hr = _native.GetName(out var pointer);

            return hr < 0
                ? AimpResult.From<string>(hr, null)
                : AimpResult.Ok(AimpString.ReadAndRelease(pointer));
        }

        public PreimageFactoryFlags GetFlags()
        {
            return (PreimageFactoryFlags)_native.GetFlags();
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