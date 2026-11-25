using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Objects;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceFileInfo"/>.
    /// </summary>
    internal sealed class AimpFileInfoService : AimpObjectWrapper, IAimpServiceFileInfo
    {
        private readonly IAIMPServiceFileInfoNative _native;

        public AimpFileInfoService(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileInfoNative>(borrowedPointer);
        }

        public bool IsExists => _native != null;

        public AimpActionResult<IAimpFileInfo> GetFileInfoFromFileUri(
            string fileUri,
            ServiceFileInfoFlags fileInfoFlags)
        {
            if (_native == null)
            {
                return AimpResult.Fail<IAimpFileInfo>();
            }

            var uri = AimpString.CreateNative(fileUri);

            try
            {
                var pointer = AimpRuntime.RequireCore().CreateObject(AimpIids.IAIMPFileInfo);
                var info = new AimpFileInfoWrapper(pointer);
                var infoPointer = info.NativePointerInternal;

                try
                {
                    var hr = _native.GetFileInfoFromFileURI(uri, (uint)fileInfoFlags, infoPointer);
                    if (hr < 0)
                    {
                        info.Dispose();
                        return AimpResult.Fail<IAimpFileInfo>();
                    }

                    return AimpResult.Ok<IAimpFileInfo>(info);
                }
                finally
                {
                    AimpComHelper.Release(infoPointer);
                }
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return AimpResult.Fail<IAimpFileInfo>();
            }
            finally
            {
                AimpComHelper.Release(uri);
            }
        }

        public AimpActionResult<IAimpFileInfo> GetFileInfoFromStream(
            IAimpStream fileStream,
            ServiceFileInfoFlags fileInfoFlags)
        {
            return AimpResult.Fail<IAimpFileInfo>();
        }

        public AimpActionResult<IAimpVirtualFile> GetVirtualFile(string fileUri)
        {
            return AimpResult.Fail<IAimpVirtualFile>();
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