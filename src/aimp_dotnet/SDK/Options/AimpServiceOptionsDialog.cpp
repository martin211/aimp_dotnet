// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceOptionsDialog.h"

using namespace AIMP::SDK;

AimpServiceOptionsDialog::
AimpServiceOptionsDialog(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceOptionsDialog>(core)
{ }

ActionResultType AimpServiceOptionsDialog::FrameModified(IAimpOptionsDialogFrame^ frame)
{
    auto service = GetAimpService();
    try
    {
        return CheckResult(service->FrameModified(_core->GetOptionsFrame()));
    }
    finally
    {
        ReleaseObject(service);
    }
}

ActionResultType AimpServiceOptionsDialog::FrameShow(IAimpOptionsDialogFrame^ frame, bool forceShow)
{
    auto service = GetAimpService();
    try
    {
        return CheckResult(service->FrameShow(_core->GetOptionsFrame(), forceShow));
    }
    finally
    {
        ReleaseObject(service);
    }
}

IAIMPServiceOptionsDialog* AimpServiceOptionsDialog::GetAimpService()
{
    IAIMPServiceOptionsDialog* service = nullptr;
    GetService(IID_IAIMPServiceOptionsDialog, &service);
    return service;
}
