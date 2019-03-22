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
#include "AimpServiceSynchronizer.h"
#include "InternalAimpTask.h"

using namespace AIMP::SDK;

AimpServiceSynchronizer::
AimpServiceSynchronizer(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceSynchronizer>(core)
{
}

AimpActionResult AimpServiceSynchronizer::ExecuteInMainThread(IAimpTask^ task, bool executeNow)
{
    IAIMPServiceSynchronizer* service = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceSynchronizer, &service) == AimpActionResult::OK)
        {
            if (service != nullptr)
            {
                InternalAimpTask* internalTask = new InternalAimpTask(task);
                return CheckResult(service->ExecuteInMainThread(internalTask, BOOL(executeNow)));
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return AimpActionResult::Fail;
}
