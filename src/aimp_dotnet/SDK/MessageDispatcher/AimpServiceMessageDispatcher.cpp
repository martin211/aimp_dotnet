// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMessageDispatcher.h"
#include "InternalAimpMessageHook.h"

using namespace AIMP::SDK;
using namespace Runtime::InteropServices;

AimpServiceMessageDispatcher::
AimpServiceMessageDispatcher(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMessageDispatcher>(core) {
}

AimpServiceMessageDispatcher::~AimpServiceMessageDispatcher() {
    _hook->Release();
    delete _hook;
    _hook = nullptr;
}

ActionResult AimpServiceMessageDispatcher::Send(AimpCoreMessageType message, int param1, IntPtr param2) {
    IAIMPServiceMessageDispatcher* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            HWND handle = nullptr;
            result = CheckResult(service->Send(DWORD(message), static_cast<int>(param1), &handle));
            if (result == ActionResultType::OK) {
                param2 = IntPtr(handle);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

int AimpServiceMessageDispatcher::Register(String^ message) {
    Assert::NotNull(message, "message");

    IAIMPServiceMessageDispatcher* service = GetAimpService();

    try {
        if (service != nullptr) {
            const pin_ptr<const WCHAR> strDate = PtrToStringChars(message);
            return service->Register(PWCHAR(strDate));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

ActionResult AimpServiceMessageDispatcher::Hook(IAimpMessageHook^ hook) {
    Assert::NotNull(hook, "hook");

    IAIMPServiceMessageDispatcher* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            _hook = new InternalAimpMessageHook(hook);
            result = CheckResult(service->Hook(_hook));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

ActionResult AimpServiceMessageDispatcher::Unhook(IAimpMessageHook^ hook) {
    IAIMPServiceMessageDispatcher* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->Unhook(_hook));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

IAIMPServiceMessageDispatcher* AimpServiceMessageDispatcher::GetAimpService() {
    IAIMPServiceMessageDispatcher* service = nullptr;
    GetService(IID_IAIMPServiceMessageDispatcher, &service);
    return service;
}
