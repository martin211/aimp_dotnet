using System.Collections.Generic;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Player.Extensions;

public interface IAimpExtensionWaveFormProvider : IAimpExtension
{
    AimpActionResult Calculate(string fileUri, IAimpTaskOwner owner, IList<IAimpWaveformPeakInfo> peaks);
}