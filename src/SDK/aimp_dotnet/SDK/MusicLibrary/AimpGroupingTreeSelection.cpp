//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpGroupingTreeSelection.h"

using namespace AIMP::SDK;

AimpGroupingTreeSelection::AimpGroupingTreeSelection(
    IAIMPMLGroupingTreeSelection* aimpObject) : AimpObject(aimpObject) {
}

int AimpGroupingTreeSelection::GetCount() {
    return InternalAimpObject->GetCount();
}

AimpActionResult<String^, Object^>^ AimpGroupingTreeSelection::GetValue(int index) {
    IAIMPString* str = nullptr;
    VARIANT val;

    String^ fieldName = nullptr;
    Object^ value = nullptr;

    const ActionResultType result = CheckResult(InternalAimpObject->GetValue(index, &str, &val));

    try {
        if (result == ActionResultType::OK) {
            if (str != nullptr) {
                fieldName = AimpConverter::ToManagedString(str);
            }

            value = AimpConverter::FromVariant(&val);
        }
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }

    return gcnew AimpActionResult<String^, Object^>(result, fieldName, value);
}
