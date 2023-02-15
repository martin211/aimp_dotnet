//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceShutdown.h"


Core::AimpServiceShutdown::AimpServiceShutdown(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceShutdown>(core) {
}

AimpActionResult^ Core::AimpServiceShutdown::Restart(String^ arguments) {
    auto service = GetAimpService();
    auto s = AimpConverter::ToAimpString(arguments);

    try {
        if (service != nullptr) {
            return gcnew AimpActionResult(CheckResult(service->Restart(s)));
        }
    }
    finally {
        ReleaseObject(s);
        ReleaseObject(service);
    }
}

AimpActionResult^ Core::AimpServiceShutdown::Shutdown(ShutdownType shutdownType) {
    auto service = GetAimpService();
    try {
        if (service != nullptr) {
            return gcnew AimpActionResult(CheckResult(service->Shutdown(static_cast<DWORD>(shutdownType))));
        }
    }
    finally {
        ReleaseObject(service);
    }
}

IAIMPServiceShutdown* Core::AimpServiceShutdown::GetAimpService() {
    IAIMPServiceShutdown* service = nullptr;
    GetService(IID_IAIMPServiceShutdown, &service);
    return service;
}
