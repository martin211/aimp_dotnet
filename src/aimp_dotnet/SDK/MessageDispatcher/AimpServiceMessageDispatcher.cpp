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
#include "AimpServiceMessageDispatcher.h"
#include "InternalAimpMessageHook.h"

using namespace AIMP::SDK;
using namespace Runtime::InteropServices;

AimpServiceMessageDispatcher::AimpServiceMessageDispatcher(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMessageDispatcher>(core)
{
    _hook = nullptr;
}

AimpServiceMessageDispatcher::~AimpServiceMessageDispatcher()
{
    _hook = nullptr;
}

AimpActionResult AimpServiceMessageDispatcher::Send(int message, int param1, IntPtr param2)
{
    IAIMPServiceMessageDispatcher* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceMessageDispatcher, &service) == AimpActionResult::OK && service != nullptr)
        {
            HWND handle = nullptr;
            result = CheckResult(service->Send(DWORD(message), int(param1), &handle));
            if (result == AimpActionResult::OK)
            {
                param2 = IntPtr(handle);
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

    return result;
}

int AimpServiceMessageDispatcher::Register(String^ message)
{
    IAIMPServiceMessageDispatcher* service = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMessageDispatcher, &service) == AimpActionResult::OK && service != nullptr)
        {
            const pin_ptr<const WCHAR> strDate = PtrToStringChars(message);
            return service->Register(PWCHAR(strDate));
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

    return 0;
}

AimpActionResult AimpServiceMessageDispatcher::Hook(IAimpMessageHook^ hook)
{
    IAIMPServiceMessageDispatcher* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (_hook == nullptr && GetService(IID_IAIMPServiceMessageDispatcher, &service) == AimpActionResult::OK && service != nullptr)
        {
            _hook = new InternalAimpMessageHook(hook);
            result = CheckResult(service->Hook(_hook));
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

    return result;
}

AimpActionResult AimpServiceMessageDispatcher::Unhook(IAimpMessageHook^ hook)
{
    IAIMPServiceMessageDispatcher* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (_hook != nullptr && GetService(IID_IAIMPServiceMessageDispatcher, &service) == AimpActionResult::OK && service != nullptr)
        {
            result = CheckResult(service->Unhook(_hook));
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

    return result;
}
