//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpConfig.h"

using namespace AIMP::SDK;

AimpConfig::AimpConfig(IAIMPConfig* aimpPlayList) : AimpObject(aimpPlayList) {
}

ActionResult AimpConfig::Delete(String^ keyPath) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->Delete(str));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult(result);
}

FloatResult AimpConfig::GetValueAsFloat(String^ keyPath) {
    IAIMPString* str = nullptr;
    double val = 0;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->GetValueAsFloat(str, &val));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<float>(result, val);
}

IntResult AimpConfig::GetValueAsInt32(String^ keyPath) {
    IAIMPString* str = nullptr;
    int val = 0;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->GetValueAsInt32(str, &val));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<int>(result, val);
}

Int64Result AimpConfig::GetValueAsInt64(String^ keyPath) {
    IAIMPString* str = nullptr;
    Int64 val = 0;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->GetValueAsInt64(str, &val));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<long long>(result, val);
}

StreamResult AimpConfig::GetValueAsStream(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPStream* stream = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->GetValueAsStream(str, &stream));

        if (result == ActionResultType::OK && stream != nullptr) {
            return gcnew AimpActionResult<IAimpStream^>(result, gcnew AimpStream(stream));
        }
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<IAimpStream^>(result, nullptr);
}

StringResult AimpConfig::GetValueAsString(String^ keyPath) {
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->GetValueAsString(str, &val));

        if (result == ActionResultType::OK && val != nullptr) {
            return gcnew AimpActionResult<String^>(result, gcnew String(val->GetData()));
        }
    }
    finally {
        // TODO Release val?
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<String^>(result, String::Empty);
}

ActionResult AimpConfig::SetValueAsFloat(String^ keyPath, float value) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->SetValueAsFloat(str, value));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return ACTION_RESULT(result)
}

ActionResult AimpConfig::SetValueAsInt32(String^ keyPath, int value) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->SetValueAsInt32(str, value));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return ACTION_RESULT(result)
}

ActionResult AimpConfig::SetValueAsInt64(String^ keyPath, Int64 value) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(InternalAimpObject->SetValueAsInt64(str, value));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return ACTION_RESULT(result)
}

ActionResult AimpConfig::SetValueAsStream(String^ keyPath, IAimpStream^ stream) {
    IAIMPString* str = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        result = CheckResult(
            InternalAimpObject->SetValueAsStream(str, static_cast<AimpStream^>(stream)->InternalAimpObject));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return ACTION_RESULT(result);
}

ActionResult AimpConfig::SetValueAsString(String^ keyPath, String^ value) {
    IAIMPString* str = nullptr;
    IAIMPString* val = nullptr;
    auto result = ActionResultType::Fail;

    try {
        str = AimpConverter::ToAimpString(keyPath);
        val = AimpConverter::ToAimpString(value);
        result = CheckResult(InternalAimpObject->SetValueAsString(str, val));
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }

        if (val != nullptr) {
            val->Release();
            val = nullptr;
        }
    }

    return ACTION_RESULT(result);
}
