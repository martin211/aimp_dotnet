// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.Options
{
    public interface IAimpOptionsDialogFrameKeyboardHelper
    {
        bool DialogKey(int charCode);

        bool SelectFirstControl();

        bool SelectNextControl(int findForward, int isTabKeyAction);
    }
}