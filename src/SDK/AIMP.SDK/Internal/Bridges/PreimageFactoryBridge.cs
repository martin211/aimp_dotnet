using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Playlist;
using AIMP.SDK;
using AIMP.SDK.PlayList.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpExtensionPlaylistPreimageFactory"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class PreimageFactoryBridge : IAIMPExtensionPlaylistPreimageFactoryNative
    {
        private readonly IAimpExtensionPlaylistPreimageFactory _factory;

        public PreimageFactoryBridge(IAimpExtensionPlaylistPreimageFactory factory)
        {
            _factory = factory ?? throw new ArgumentNullException(nameof(factory));
        }

        [PreserveSig]
        public int CreatePreimage(out IntPtr preimage)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var managed = _factory.CreatePreimage();
                if (managed.ResultType != ActionResultType.OK || managed.Result == null)
                {
                    return (int)managed.ResultType;
                }

                result = AimpComHelper.GetPointer(
                    new PreimageBridge(managed.Result),
                    typeof(IAIMPPlaylistPreimageNative));

                return Safe.S_OK;
            });

            preimage = result;
            return hr;
        }

        [PreserveSig]
        public int GetID(out IntPtr id)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var value = _factory.GetId();
                if (value.ResultType == ActionResultType.OK)
                {
                    result = AimpString.CreateNative(value.Result ?? string.Empty);
                }

                return (int)value.ResultType;
            });

            id = result;
            return hr;
        }

        [PreserveSig]
        public int GetName(out IntPtr name)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var value = _factory.GetName();
                if (value.ResultType == ActionResultType.OK)
                {
                    result = AimpString.CreateNative(value.Result ?? string.Empty);
                }

                return (int)value.ResultType;
            });

            name = result;
            return hr;
        }

        [PreserveSig]
        public uint GetFlags()
        {
            return (uint)_factory.GetFlags();
        }
    }
}