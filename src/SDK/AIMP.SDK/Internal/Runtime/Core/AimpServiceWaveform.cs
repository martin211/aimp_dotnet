using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Player;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpServiceWaveform"/> (marker service).
    /// </summary>
    internal sealed class AimpServiceWaveform : AimpObjectWrapper, IAimpServiceWaveform
    {
        public bool IsExists => true;
    }
}