using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for <see cref="IAimpExtensionFileFormat"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class FileFormatBridge : IAIMPExtensionFileFormatNative
    {
        private readonly IAimpExtensionFileFormat _provider;

        public FileFormatBridge(IAimpExtensionFileFormat provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        public int GetDescription(out IntPtr text)
        {
            return WriteString(_provider.Description, out text);
        }

        public int GetExtList(out IntPtr text)
        {
            return WriteString(_provider.ExtList, out text);
        }

        public int GetFlags(out uint flags)
        {
            var result = _provider.Flags;
            if (result == null)
            {
                flags = 0;
                return Safe.E_FAIL;
            }

            flags = result.ResultType == ActionResultType.OK ? (uint)result.Result : 0;
            return (int)result.ResultType;
        }

        private static int WriteString(AimpActionResult<string> result, out IntPtr text)
        {
            if (result == null)
            {
                text = IntPtr.Zero;
                return Safe.E_FAIL;
            }

            if (result.ResultType != ActionResultType.OK)
            {
                text = IntPtr.Zero;
                return (int)result.ResultType;
            }

            text = AimpString.CreateNative(result.Result ?? string.Empty);
            return Safe.S_OK;
        }
    }
}