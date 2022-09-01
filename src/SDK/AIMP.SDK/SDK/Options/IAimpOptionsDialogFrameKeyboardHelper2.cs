//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Options;

public interface IAimpOptionsDialogFrameKeyboardHelper2 : IAimpOptionsDialogFrameKeyboardHelper
{
    /// <summary>
    /// Selects the last control.
    /// </summary>
    /// <returns></returns>
    bool SelectLastControl();
}