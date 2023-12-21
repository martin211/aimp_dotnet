//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpServicePlayerEqualizerPresets.h"
#include "AimpEqualizerPreset.h"

AimpActionResult<IAimpEqualizerPreset^>^ AimpServicePlayerEqualizerPresets::Add(String^ name) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* str = nullptr;

    try {
        if (service != nullptr) {
            IAIMPEqualizerPreset* preset = nullptr;
            str = AimpConverter::ToAimpString(name);
            result = CheckResult(service->Add(str, IID_IAIMPEqualizerPreset,reinterpret_cast<void**>(&preset)));
            if (result == ActionResultType::OK) {
                return gcnew AimpActionResult<IAimpEqualizerPreset^>(result, gcnew AimpEqualizerPreset(preset));
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpEqualizerPreset^>(result);
}

AimpActionResult<IAimpEqualizerPreset^>^ AimpServicePlayerEqualizerPresets::FindByName(String^ name) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* str = nullptr;

    try {
        if (service != nullptr) {
            IAIMPEqualizerPreset* preset = nullptr;
            str = AimpConverter::ToAimpString(name);
            result = CheckResult(service->FindByName(str, IID_IAIMPEqualizerPreset, reinterpret_cast<void**>(&preset)));
            if (result == ActionResultType::OK) {
                return gcnew AimpActionResult<IAimpEqualizerPreset^>(result, gcnew AimpEqualizerPreset(preset));
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpEqualizerPreset^>(result);
}

AimpActionResult^ AimpServicePlayerEqualizerPresets::Delete(IAimpEqualizerPreset^ preset) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            const auto managedObj = static_cast<AimpEqualizerPreset^>(preset);
            result = CheckResult(service->Delete(managedObj->ComObject));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult^ AimpServicePlayerEqualizerPresets::Delete(int index) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->Delete2(index));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult<IAimpEqualizerPreset^>^ AimpServicePlayerEqualizerPresets::GetPreset(int index) {
    const auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPEqualizerPreset* preset = nullptr;

    try {
        if (service != nullptr) {
            result = CheckResult(service->GetPreset(index, IID_IAIMPEqualizerPreset, reinterpret_cast<void**>(&preset)));
            if (result == ActionResultType::OK) {
                return gcnew AimpActionResult<IAimpEqualizerPreset^>(result, gcnew AimpEqualizerPreset(preset));
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpEqualizerPreset^>(result);
}

int AimpServicePlayerEqualizerPresets::GetPresetCount() {
    const auto service = GetAimpService();

    try {
        if (service != nullptr) {
            return service->GetPresetCount();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

IAIMPServicePlayerEqualizerPresets* AimpServicePlayerEqualizerPresets::GetAimpService() {
    IAIMPServicePlayerEqualizerPresets* service = nullptr;
    _core->GetService(IID_IAIMPServicePlayerEqualizerPresets, reinterpret_cast<void**>(&service));
    return service;
}
