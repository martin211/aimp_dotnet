// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceSynchronizer.h"
#include "InternalAimpTask.h"

using namespace AIMP::SDK;

AimpServiceSynchronizer::
AimpServiceSynchronizer(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceSynchronizer>(core) {
}

ActionResult AimpServiceSynchronizer::ExecuteInMainThread(IAimpTask^ task, bool executeNow) {
    IAIMPServiceSynchronizer* service = GetAimpService();

    try {
        if (service != nullptr) {
            InternalAimpTask* internalTask = new InternalAimpTask(task);
            return ACTION_RESULT(CheckResult(service->ExecuteInMainThread(internalTask, BOOL(executeNow))));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(ActionResultType::Fail);
}

IAIMPServiceSynchronizer* AimpServiceSynchronizer::GetAimpService() {
    IAIMPServiceSynchronizer* service = nullptr;
    GetService(IID_IAIMPServiceSynchronizer, &service);
    return service;
}
