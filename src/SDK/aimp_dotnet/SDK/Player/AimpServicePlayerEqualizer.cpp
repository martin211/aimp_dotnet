//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpServicePlayerEqualizer.h"
#include "AimpEqualizerPreset.h"

bool AimpServicePlayerEqualizer::GetActive() {
    const auto service = QueryInterface();
    try {
        if (service != nullptr) {
            return service->GetActive();
        }

        return false;
    }
    finally {
        ReleaseObject(service);
    }
}

ActionResult AimpServicePlayerEqualizer::SetActive(bool value) {
    const auto service = QueryInterface();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->SetActive(value));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

DoubleResult AimpServicePlayerEqualizer::GetPreamp() {
    const auto service = QueryInterface();
    ActionResultType result = ActionResultType::Fail;
    double val = 0;

    try {
        if (service != nullptr) {
            result = CheckResult(service->GetPreamp(&val));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return DOUBLE_RESULT(result, val);
}

ActionResult AimpServicePlayerEqualizer::SetPreamp(double value) {
    const auto service = QueryInterface();
    ActionResultType result = ActionResultType::Fail;

    if (value < -15 || value > 15) {
        throw gcnew ArgumentOutOfRangeException("value", "Preamp value should be between -15 and +15");
    }

    try {
        if (service != nullptr) {
            result = CheckResult(service->SetPreamp(value));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult<IAimpEqualizerPreset^>^ AimpServicePlayerEqualizer::GetPreset() {
    const auto service = QueryInterface();
    ActionResultType result = ActionResultType::Fail;
    IAIMPEqualizerPreset* preset = nullptr;

    try {
        if (service != nullptr) {
            result = CheckResult(service->GetPreset(IID_IAIMPEqualizerPreset, reinterpret_cast<void**>(&preset)));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpEqualizerPreset^>(result, nullptr);
}

ActionResult AimpServicePlayerEqualizer::SetPreset(IAimpEqualizerPreset^ value) {
    const auto service = QueryInterface();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->SetPreset(static_cast<IAIMPEqualizerPreset*>(static_cast<AimpEqualizerPreset^>(value)->InternalAimpObject)));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

bool AimpServicePlayerEqualizer::IsExists::get() {
    return QueryInterface() != nullptr;
}

IAIMPServicePlayerEqualizer* AimpServicePlayerEqualizer::QueryInterface() {
    IAIMPServicePlayerEqualizer* service = nullptr;
    _core->GetService(IID_IAIMPServicePlayerEqualizer, reinterpret_cast<void**>(&service));
    _aimpObject = service;
    return service;
}

void AimpServicePlayerEqualizer::ReleaseObject(IUnknown* object) {
    if (object != nullptr) {
        if (object->Release() == 0) {
            object = nullptr;
        }
    }
}
