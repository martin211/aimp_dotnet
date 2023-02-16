//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "PropertyListHelper.h"


#define VALIDATE_RESULT(result, message) { if (result != ActionResultType::OK) { ACTION_ERROR2(result, message) } }


using namespace AIMP::SDK;

void PropertyListExtension::SetObject(IAIMPPropertyList* propertyList, int propertyId, IUnknown* value) {
    const auto result = Utils::CheckResult(propertyList->SetValueAsObject(propertyId, value));
    VALIDATE_RESULT(result, "Unable to set Object property.")
}

void PropertyListExtension::SetString(IAIMPPropertyList* propertyList, int propertyId, String^ value) {
    Assert::NotNull(value, "value");

    IAIMPString* str = nullptr;
    try {
        str = AimpConverter::ToAimpString(value);
        SetObject(propertyList, propertyId, str);
    }
    finally {
        str->Release();
        str = nullptr;
    }
}

void PropertyListExtension::SetInt32(IAIMPPropertyList* propertyList, int propertyId, int value) {
    const auto result = Utils::CheckResult(propertyList->SetValueAsInt32(propertyId, value));

    VALIDATE_RESULT(result, "Unable to set Int32 property.")
}

void PropertyListExtension::SetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64 value) {
    const auto result = Utils::CheckResult(propertyList->SetValueAsInt64(propertyId, value));

    VALIDATE_RESULT(result, "Unable to set Int64 property.")
}

void PropertyListExtension::SetFloat(IAIMPPropertyList* propertyList, int propertyId, double value) {
    const auto result = Utils::CheckResult(propertyList->SetValueAsFloat(propertyId, value));

    VALIDATE_RESULT(result, "Unable to set Float property.")
}

void PropertyListExtension::SetBool(IAIMPPropertyList* propertyList, int propertyId, bool value) {
    SetInt32(propertyList, propertyId, value ? 1 : 0);
}

void PropertyListExtension::GetString(IAIMPPropertyList* propertyList, int propertyId, String^% value) {
    IAIMPString* str = nullptr;
    String^ val = String::Empty;

    try {
        const auto result = Utils::CheckResult(
            propertyList->GetValueAsObject(propertyId, IID_IAIMPString, reinterpret_cast<void**>(&str)));

        VALIDATE_RESULT(result, "Unable to get string property.")

        if (str != nullptr) {
            GetString(str, val);
            value = val;
        }
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }
}

void PropertyListExtension::GetString(IAIMPString* aimpString, String^% value) {
    value = gcnew String(aimpString->GetData());
}

ActionResultType PropertyListExtension::GetObject(IAIMPPropertyList* propertyList, int propertyId, REFIID objectId,
                                                  void** value) {
    const auto result = Utils::CheckResult(propertyList->GetValueAsObject(propertyId, objectId, value));
    VALIDATE_RESULT(result, "Unable to get a object property.")
    return result;
}

ActionResultType PropertyListExtension::GetInt32(IAIMPPropertyList* propertyList, int propertyId, int% value) {
    int val = 0;
    const auto result = Utils::CheckResult(propertyList->GetValueAsInt32(propertyId, &val));
    VALIDATE_RESULT(result, "Unable to get a Int32 property.")
    value = val;
    return result;
}

ActionResultType PropertyListExtension::GetInt64(IAIMPPropertyList* propertyList, int propertyId, Int64% value) {
    Int64 val = 0;
    const auto result = Utils::CheckResult(propertyList->GetValueAsInt64(propertyId, &val));
    VALIDATE_RESULT(result, "Unable to get a Int64 property.")
    value = val;
    return result;
}

ActionResultType PropertyListExtension::GetFloat(IAIMPPropertyList* propertyList, int propertyId, double% value) {
    double val = 0;
    const auto result = Utils::CheckResult(propertyList->GetValueAsFloat(propertyId, &val));
    //VALIDATE_RESULT(result, "Unable to get a Float property.")
    value = val;
    return result;
}

ActionResultType PropertyListExtension::GetBool(IAIMPPropertyList* propertyList, int propertyId, bool% value) {
    int val = 0;
    const auto result = Utils::CheckResult(propertyList->GetValueAsInt32(propertyId, &val));
    VALIDATE_RESULT(result, "Unable to get a Bool property.")
    value = val != 0;
    return result;
}

String^ PropertyListExtension::GetString(IAIMPPropertyList* propertyList, int propertyId) {
    String^ val = String::Empty;
    GetString(propertyList, propertyId, *&val);
    return val;
}

int PropertyListExtension::GetInt32(IAIMPPropertyList* propertyList, int propertyId) {
    int val = 0;
    GetInt32(propertyList, propertyId, val);
    return val;
}

Int64 PropertyListExtension::GetInt64(IAIMPPropertyList* propertyList, int propertyId) {
    Int64 val = 0;
    GetInt64(propertyList, propertyId, val);
    return val;
}

double PropertyListExtension::GetFloat(IAIMPPropertyList* propertyList, int propertyId) {
    double val = 0;
    GetFloat(propertyList, propertyId, val);
    return val;
}

bool PropertyListExtension::GetBool(IAIMPPropertyList* propertyList, int propertyId) {
    bool val = false;
    GetBool(propertyList, propertyId, val);
    return val;
}

ActionResultType PropertyListExtension::GetVariant(IAIMPPropertyList2* propertyList, int propertyId, Object^% value) {
    VARIANT* val = nullptr;
    const auto result = Utils::CheckResult(propertyList->GetValueAsVariant(propertyId, val));
    VALIDATE_RESULT(result, "Unable to get a Variant property.")
    value = AimpConverter::FromVariant(val);
    return result;
}

ActionResultType PropertyListExtension::SetVariant(IAIMPPropertyList2* propertyList, int propertyId, Object^% val) {
    return ActionResultType::NotImplemented;
}
