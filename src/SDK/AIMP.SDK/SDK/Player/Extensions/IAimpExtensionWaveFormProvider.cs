//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Threading;

namespace AIMP.SDK.Player.Extensions;

/// <summary>
/// This is an extension for the IAimpServiceWaveform service that allows to plugin register custom data provider for the waveform-navigator.
/// </summary>
public interface IAimpExtensionWaveFormProvider : IAimpExtension
{
    /// <summary>
    /// Calculate peak info.
    /// </summary>
    /// <param name="fileUri">The file uri.</param>
    /// <param name="owner">This interface provides an ability to check if task is canceling.
    /// Refer to the IAimpTask for usage recommendations.</param>
    /// <param name="peaks">Plugin must calculate the "wave" for the FileURI in resolution of PeakCount points and populate this array.</param>
    /// <returns></returns>
    AimpActionResult Calculate(string fileUri, IAimpTaskOwner owner, IList<IAimpWaveformPeakInfo> peaks);
}