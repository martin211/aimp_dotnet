/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpServiceOptionsDialog.h"

using namespace AIMP::SDK;

AimpServiceOptionsDialog::AimpServiceOptionsDialog(ManagedAimpCore ^core) : AimpBaseManager<IAIMPServiceOptionsDialog>(core)
{
    IAIMPServiceOptionsDialog *service;
    core->GetService(IID_IAIMPServiceOptionsDialog, (void**)&service);
    _service = service;
}

AimpActionResult AimpServiceOptionsDialog::FrameModified(IAimpOptionsDialogFrame ^frame)
{
    return CheckResult(_service->FrameModified(_core->GetOptionsFrame()));
}

AimpActionResult AimpServiceOptionsDialog::FrameShow(IAimpOptionsDialogFrame ^frame, bool forceShow)
{
    return CheckResult(_service->FrameShow(_core->GetOptionsFrame(), forceShow));
}
