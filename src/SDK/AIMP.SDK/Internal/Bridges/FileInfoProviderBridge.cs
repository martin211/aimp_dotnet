using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges the v1 <see cref="IAimpExtensionFileInfoProvider"/> to the two
    /// native vtables (<c>IAIMPExtensionFileInfoProvider</c> and
    /// <c>IAIMPExtensionFileInfoProviderEx</c>).
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class FileInfoProviderBridge :
        IAIMPExtensionFileInfoProviderNative,
        IAIMPExtensionFileInfoProviderExNative,
        ICustomQueryInterface
    {
        private readonly IAimpExtensionFileInfoProvider _provider;

        public FileInfoProviderBridge(IAimpExtensionFileInfoProvider provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        public CustomQueryInterfaceResult GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IUnknown ||
                iid == AimpIids.IAIMPExtensionFileInfoProvider ||
                iid == AimpIids.IAIMPExtensionFileInfoProviderEx)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            return CustomQueryInterfaceResult.Failed;
        }

        [PreserveSig]
        int IAIMPExtensionFileInfoProviderNative.GetFileInfo(IntPtr fileUri, IntPtr info)
        {
            return Safe.Run(() =>
            {
                var target = new AimpFileInfoWrapper(AimpComHelper.AddRef(info));

                try
                {
                    IAimpFileInfo current = target;
                    var result = _provider.GetFileInfo(AimpString.Read(fileUri), ref current);

                    if (result.ResultType == ActionResultType.OK &&
                        current != null &&
                        !ReferenceEquals(current, target))
                    {
                        target.Assign(current);
                    }

                    return ToHResult(result);
                }
                finally
                {
                    target.Dispose();
                }
            });
        }

        [PreserveSig]
        int IAIMPExtensionFileInfoProviderExNative.GetFileInfo(IntPtr stream, IntPtr info)
        {
            return Safe.Run(() =>
            {
                var target = new AimpFileInfoWrapper(AimpComHelper.AddRef(info));

                try
                {
                    using (IAimpStream source = new AimpStreamWrapper(stream))
                    {
                        IAimpFileInfo current = target;
                        var result = _provider.GetFileInfo(source, ref current);

                        if (result.ResultType == ActionResultType.OK &&
                            current != null &&
                            !ReferenceEquals(current, target))
                        {
                            target.Assign(current);
                        }

                        return ToHResult(result);
                    }
                }
                finally
                {
                    target.Dispose();
                }
            });
        }

        private static int ToHResult(AimpActionResult result)
        {
            return result == null ? Safe.E_FAIL : (int)result.ResultType;
        }
    }
}