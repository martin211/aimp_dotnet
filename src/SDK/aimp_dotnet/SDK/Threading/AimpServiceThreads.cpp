//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceThreads.h"
#include "InternalAimpTask.h"

using namespace AIMP::SDK;

AimpServiceThreads::AimpServiceThreads(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceThreads>(core) {
}

AimpActionResult^ AimpServiceThreads::Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags) {
    const auto service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->Cancel(reinterpret_cast<DWORD_PTR>(taskHandle.ToPointer()), static_cast<DWORD>(flags)));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult^ AimpServiceThreads::WaitFor(UIntPtr taskHandle) {
    const auto service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->WaitFor(reinterpret_cast<DWORD_PTR>(taskHandle.ToPointer())));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult^ AimpServiceThreads::ExecuteInMainThread(IAimpTask^ task, AimpServiceThreadPoolType flags) {
    const auto service = GetAimpService();

    try {
        if (service != nullptr) {
            InternalAimpTask* internalTask = new InternalAimpTask(task);
            const auto result = service->ExecuteInMainThread(internalTask, static_cast<DWORD>(flags));
            return ACTION_RESULT(CheckResult(result));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(ActionResultType::Fail);
}

AimpActionResult<UIntPtr>^ AimpServiceThreads::ExecuteInThread(IAimpTask^ task) {
    const auto service = GetAimpService();
    auto result = ActionResultType::Fail;
    auto handle = UIntPtr(static_cast<void*>(0));

    try {
        DWORD_PTR h;

        if (service != nullptr) {
            InternalAimpTask* internalTask = new InternalAimpTask(task);
            result = CheckResult(service->ExecuteInThread(internalTask, &h));
            handle = UIntPtr(reinterpret_cast<void*>(h));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<UIntPtr>(result, handle);
}

IAIMPServiceThreads* AimpServiceThreads::GetAimpService() {
    IAIMPServiceThreads* service = nullptr;
    GetService(IID_IAIMPServiceThreads, &service);
    return service;
}
