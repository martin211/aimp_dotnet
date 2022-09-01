//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceOptionsDialog.h"

using namespace AIMP::SDK;

AimpServiceOptionsDialog::
AimpServiceOptionsDialog(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceOptionsDialog>(core) {
}

ActionResult AimpServiceOptionsDialog::FrameModified(IAimpOptionsDialogFrame^ frame) {
    auto service = GetAimpService();
    try {
        return ACTION_RESULT(CheckResult(service->FrameModified(_core->GetOptionsFrame())));
    }
    finally {
        ReleaseObject(service);
    }
}

ActionResult AimpServiceOptionsDialog::FrameShow(IAimpOptionsDialogFrame^ frame, bool forceShow) {
    auto service = GetAimpService();
    try {
        return ACTION_RESULT(CheckResult(service->FrameShow(_core->GetOptionsFrame(), forceShow)));
    }
    finally {
        ReleaseObject(service);
    }
}

IAIMPServiceOptionsDialog* AimpServiceOptionsDialog::GetAimpService() {
    IAIMPServiceOptionsDialog* service = nullptr;
    GetService(IID_IAIMPServiceOptionsDialog, &service);
    return service;
}
