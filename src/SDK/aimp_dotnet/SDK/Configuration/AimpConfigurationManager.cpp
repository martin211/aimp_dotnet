//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpConfigurationManager.h"

AimpServiceConfig::AimpServiceConfig(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceConfig>(core) {
}

AimpServiceConfig::~AimpServiceConfig() {
}

ActionResult AimpServiceConfig::FlushCache() {
    IAIMPServiceConfig* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->FlushCache());
        }
    }
    finally {
        ReleaseObject(service);
    }

    return GetResult(result);
}

ActionResult AimpServiceConfig::Delete(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->Delete(str));
        }
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }

        if (service != nullptr) {
            service->Release();
            service = nullptr;
        }
    }

    return GetResult(result);
}

FloatResult AimpServiceConfig::GetValueAsFloat(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    double val = 0;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        if (service != nullptr) {
            result = CheckResult(service->GetValueAsFloat(str, &val));
        }

        return gcnew AimpActionResult<float>(result, val);
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }
}

IntResult AimpServiceConfig::GetValueAsInt32(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    int val = 0;
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->GetValueAsInt32(str, &val));
        }

        return gcnew AimpActionResult<int>(result, val);
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }
}

Int64Result AimpServiceConfig::GetValueAsInt64(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    Int64 val = 0;
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->GetValueAsInt64(str, &val));
        }

        return gcnew AimpActionResult<long long>(result, val);
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }
}

StreamResult AimpServiceConfig::GetValueAsStream(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPStream* stream = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->GetValueAsStream(str, &stream));
        }

        if (result == ActionResultType::OK) {
            return gcnew AimpActionResult<IAimpStream^>(result, gcnew AimpStream(stream));
        }

        return gcnew AimpActionResult<IAimpStream^>(result);
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }
}

StringResult AimpServiceConfig::GetValueAsString(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    IAIMPServiceConfig* service = GetAimpService();
    auto result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->GetValueAsString(str, &val));
        }

        if (val != nullptr) {
            return gcnew AimpActionResult<String^>(result, gcnew String(val->GetData()));
        }
    }
    finally {
        // TODO Release val?
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<String^>(result);
}

ActionResult AimpServiceConfig::SetValueAsFloat(String^ keyPath, float value) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsFloat(str, value));
        }
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

ActionResult AimpServiceConfig::SetValueAsInt32(String^ keyPath, int value) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsInt32(str, value));
        }
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

ActionResult AimpServiceConfig::SetValueAsInt64(String^ keyPath, Int64 value) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsInt64(str, value));
        }
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

ActionResult AimpServiceConfig::SetValueAsStream(String^ keyPath, IAimpStream^ stream) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            result = CheckResult(service->SetValueAsStream(str, static_cast<AimpStream^>(stream)->InternalAimpObject));
        }
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

ActionResult AimpServiceConfig::SetValueAsString(String^ keyPath, String^ value) {
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    auto result = ActionResultType::Fail;
    IAIMPServiceConfig* service = GetAimpService();

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(keyPath);
            val = AimpConverter::ToAimpString(value);
            result = CheckResult(service->SetValueAsString(str, val));
        }
    }
    finally {
        ReleaseObject(str);
        ReleaseObject(val);
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

IAIMPServiceConfig* AimpServiceConfig::GetAimpService() {
    IAIMPServiceConfig* service = nullptr;
    GetService(IID_IAIMPServiceConfig, &service);
    return service;
}
