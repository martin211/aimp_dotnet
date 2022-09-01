//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Player.Extensions;

public interface IAimpExtensionWaveFormProvider : IAimpExtension
{
    AimpActionResult Calculate(string fileUri, IAimpTaskOwner owner, IList<IAimpWaveformPeakInfo> peaks);
}