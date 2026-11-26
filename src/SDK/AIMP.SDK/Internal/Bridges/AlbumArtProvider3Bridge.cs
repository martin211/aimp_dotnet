using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.AlbumArt;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.AlbumArt.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for <see cref="IAimpExtensionAlbumArtProvider3"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class AlbumArtProvider3Bridge : IAIMPExtensionAlbumArtProvider3Native
    {
        private readonly IAimpExtensionAlbumArtProvider3 _provider;

        public AlbumArtProvider3Bridge(IAimpExtensionAlbumArtProvider3 provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        public int Get(IntPtr fileInfo, IntPtr request, out IntPtr image)
        {
            var resultPointer = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var file = fileInfo == IntPtr.Zero
                    ? null
                    : new AimpFileInfoWrapper(AimpComHelper.AddRef(fileInfo));

                try
                {
                    var result = _provider.Get(file, null);
                    if (result == null)
                    {
                        return Safe.E_FAIL;
                    }

                    if (result.ResultType != ActionResultType.OK)
                    {
                        return (int)result.ResultType;
                    }

                    var native = result.Result as IAimpNativeObject;
                    if (native == null)
                    {
                        return Safe.E_FAIL;
                    }

                    resultPointer = native.NativePointer;
                    return Safe.S_OK;
                }
                finally
                {
                    file?.Dispose();
                }
            });

            image = resultPointer;
            return hr;
        }

        public uint GetCategory()
        {
            return (uint)_provider.GetCategory();
        }
    }
}