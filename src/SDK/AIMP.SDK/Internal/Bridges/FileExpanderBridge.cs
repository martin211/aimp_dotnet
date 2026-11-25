using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for <see cref="IAimpExtensionFileExpander"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class FileExpanderBridge : IAIMPExtensionFileExpanderNative
    {
        private readonly IAimpExtensionFileExpander _provider;

        public FileExpanderBridge(IAimpExtensionFileExpander provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        public int Expand(IntPtr fileName, out IntPtr list, IntPtr progressCallback)
        {
            // Virtual file objects are not projected yet; keep the extension registrable.
            list = IntPtr.Zero;
            return Safe.E_NOTIMPL;
        }
    }
}