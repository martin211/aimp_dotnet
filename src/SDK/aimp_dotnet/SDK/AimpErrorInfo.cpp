// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "stdafx.h"
#include "AimpErrorInfo.h"

using namespace AIMP::SDK;

AimpErrorInfo::AimpErrorInfo(IAIMPErrorInfo* obj) : AimpObject(obj) {
    _aimpObject = obj;
    _aimpObject->AddRef();
}

AimpErrorInfo::~AimpErrorInfo() {
    this->!AimpErrorInfo();
}

AimpErrorInfo::!AimpErrorInfo() {
    _aimpObject->Release();
}

AimpActionResult<ErrorInfo^>^ AimpErrorInfo::GetInfo() {
    int errorCode = 0;
    IAIMPString* message = nullptr;
    IAIMPString* details = nullptr;
    const auto res = CheckResult(_aimpObject->GetInfo(&errorCode, &message, &details));

    int code = errorCode;

    if (res == ActionResultType::OK) {
        try {
            return gcnew AimpActionResult<ErrorInfo^>(res, gcnew ErrorInfo(
                code,
                AimpConverter::ToManagedString(message),
                AimpConverter::ToManagedString(details)
            ));
        } finally {
            message->Release();
            details->Release();
        }
    }

    return gcnew AimpActionResult<ErrorInfo^>(res);
}

AimpActionResult<String^>^ AimpErrorInfo::GetInfoFormatted() {
    IAIMPString* s = nullptr;
    const auto res = CheckResult(_aimpObject->GetInfoFormatted(&s));

    if (res == ActionResultType::OK) {
        try {
            return gcnew AimpActionResult<String^>(res, AimpConverter::ToManagedString(s));
        } finally {
            s->Release();
        }
    }

    return gcnew AimpActionResult<String^>(res);
}

void AimpErrorInfo::SetInfo(int errorCode, String^ message, String^ details) {
    _aimpObject->SetInfo(
        errorCode,
        AimpConverter::ToAimpString(message),
        AimpConverter::ToAimpString(details));
}
