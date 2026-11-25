using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Commands;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceFileSystems"/>.
    /// </summary>
    internal sealed class AimpFileSystemsService : AimpObjectWrapper, IAimpServiceFileSystems
    {
        private readonly IAIMPServiceFileSystemsNative _native;

        public AimpFileSystemsService(IntPtr borrowedPointer)
        {
            _native = AimpComHelper.WrapBorrowed<IAIMPServiceFileSystemsNative>(borrowedPointer);
        }

        public bool IsExists => _native != null;

        public AimpActionResult<IAimpFileSystemCommand> Get(
            FileCommandType commandType,
            string fileUri)
        {
            return AimpResult.Fail<IAimpFileSystemCommand>();
        }

        public AimpActionResult<IAimpFileSystemCommand> GetDefault(FileCommandType commandType)
        {
            return AimpResult.Fail<IAimpFileSystemCommand>();
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