//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceThreadPool.h"
#include "InternalAimpTask.h"

using namespace AIMP::SDK;

AimpServiceThreadPool::AimpServiceThreadPool(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceThreadPool>(core) {
}

ActionResult AimpServiceThreadPool::Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags) {
    IAIMPServiceThreadPool* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->Cancel(DWORD_PTR(taskHandle.ToPointer()), DWORD(flags)));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult<UIntPtr>^ AimpServiceThreadPool::Execute(IAimpTask^ task) {
    IAIMPServiceThreadPool* service = GetAimpService();
    auto result = ActionResultType::Fail;
    auto handle = UIntPtr(static_cast<void*>(0));

    try {
        DWORD_PTR h;

        if (service != nullptr) {
            InternalAimpTask* internalTask = new InternalAimpTask(task);
            result = CheckResult(service->Execute(internalTask, &h));
            handle = UIntPtr(reinterpret_cast<void*>(h));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<UIntPtr>(result, handle);
}

ActionResult AimpServiceThreadPool::WaitFor(UIntPtr handle) {
    IAIMPServiceThreadPool* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->WaitFor(reinterpret_cast<DWORD_PTR>(handle.ToPointer())));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

IAIMPServiceThreadPool* AimpServiceThreadPool::GetAimpService() {
    IAIMPServiceThreadPool* service = nullptr;
    GetService(IID_IAIMPServiceThreadPool, &service);
    return service;
}
