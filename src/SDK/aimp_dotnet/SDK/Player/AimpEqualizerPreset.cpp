//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpEqualizerPreset.h"
#include "SDK/Objects/AimpString.h"

AimpEqualizerPreset::AimpEqualizerPreset(IAIMPEqualizerPreset* obj) : AimpEqualizerBands(obj) {
    _aimpObject = obj;
}

StringActionResult^ AimpEqualizerPreset::GetName() {
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* str = nullptr;
    IAimpString^ mStr = nullptr;

    result = CheckResult(static_cast<IAIMPEqualizerPreset*>(InternalAimpObject)->GetName(&str));

    if (result == ActionResultType::OK) {
        mStr = gcnew AimpString(str);
    }

    return gcnew StringActionResult(result, mStr);
}

AimpActionResult^ AimpEqualizerPreset::SetName(IAimpString^ value) {
    const auto result = CheckResult(static_cast<IAIMPEqualizerPreset*>(InternalAimpObject)->SetName(static_cast<AimpString^>(value)->InternalAimpObject));
    return ACTION_RESULT(result);
}
