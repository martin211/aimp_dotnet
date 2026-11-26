using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Player;
using AIMP.SDK.Player.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for <see cref="IAimpExtensionWaveFormProvider"/>.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class WaveformProviderBridge : IAIMPExtensionWaveformProviderNative
    {
        private readonly IAimpExtensionWaveFormProvider _provider;

        public WaveformProviderBridge(IAimpExtensionWaveFormProvider provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        public int Calculate(IntPtr fileUri, IntPtr taskOwner, IntPtr peaks, int peakCount)
        {
            // Waveform peak objects are not projected yet; keep the extension registrable.
            return Safe.E_NOTIMPL;
        }
    }
}