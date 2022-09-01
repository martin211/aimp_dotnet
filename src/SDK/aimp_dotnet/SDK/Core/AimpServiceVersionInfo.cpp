//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceVersionInfo.h"

AimpServiceVersionInfo::AimpServiceVersionInfo(ManagedAimpCore^ core) : BaseAimpService<
    IAIMPServiceVersionInfo>(core) {
}

String^ AimpServiceVersionInfo::FormatInfo::get() {
    auto service = GetAimpService();
    IAIMPString* s = nullptr;
    ActionResultType res = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            res = CheckResult(service->FormatInfo(&s));
            if (res == ActionResultType::OK && s != nullptr) {
                return AimpConverter::ToManagedString(s);
            }
        }
    } finally {
        ReleaseObject(service);
        ReleaseObject(s);
    }

    return String::Empty;
}

DateTime AimpServiceVersionInfo::BuildDate::get() {
    auto service = GetAimpService();

    try {
        if (service != nullptr) {
            int d = service->GetBuildDate();
            auto year = HIWORD(d);
            auto month = HIBYTE(d);
            auto day = LOBYTE(d);
            auto dt = gcnew DateTime(year, month, day);
            return dt->AddMilliseconds(1);
        }
    }
    finally {
        ReleaseObject(service);
    }

    return DateTime::MinValue;
}

Core::BuildStateType AimpServiceVersionInfo::BuildState::get() {
    auto service = GetAimpService();

    try {
        if (service != nullptr) {
            return static_cast<Core::BuildStateType>(service->GetBuildState());
        }
    }
    finally {
        ReleaseObject(service);
    }

    return Core::BuildStateType::Alpha;
}

int AimpServiceVersionInfo::BuildNumber::get() {
    auto service = GetAimpService();

    try {
        if (service != nullptr) {
            return service->GetBuildNumber();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

int AimpServiceVersionInfo::VersionId::get() {
    auto service = GetAimpService();

    try {
        if (service != nullptr) {
            return service->GetVersionID();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

IAIMPServiceVersionInfo* AimpServiceVersionInfo::GetAimpService() {
    IAIMPServiceVersionInfo* service = nullptr;
    GetService(IID_IAIMPServiceVersionInfo, &service);
    return service;
}
