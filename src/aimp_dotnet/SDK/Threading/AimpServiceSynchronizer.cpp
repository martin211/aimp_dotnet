// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceSynchronizer.h"

using namespace AIMP::SDK;

AimpServiceSynchronizer::AimpServiceSynchronizer(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceSynchronizer>(core)
{

}

AimpActionResult AimpServiceSynchronizer::ExecuteInMainThread(IAimpTask^ task, bool executeNow)
{
    IAIMPServiceSynchronizer *service = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceSynchronizer, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                InternalAimpTask *internalTask = new InternalAimpTask(task);
                return CheckResult(service->ExecuteInMainThread(internalTask, (BOOL)executeNow));
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }
    }

    return AIMP::SDK::AimpActionResult::Fail;
}
