// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMusicLibrary.h"
#include "AimpDataStorage.h"

using namespace AIMP::SDK;

AimpActionResult<IAimpDataStorage^>^ AimpServiceMusicLibrary::GetActiveStorage() {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAimpDataStorage^ storage = nullptr;

    try {
        if (service != nullptr) {
            IAIMPMLDataStorage* aimpStorage = nullptr;
            result = CheckResult(
                service->GetActiveStorage(IID_IAIMPMLDataStorage, reinterpret_cast<void**>(&aimpStorage)));
            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpDataStorage(aimpStorage);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpDataStorage^>(result, storage);
}

AimpActionResult<IAimpGroupingPresets^>^ AimpServiceMusicLibrary::GetActiveGroupingPresets() {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAimpGroupingPresets^ presets = nullptr;

    try {
        if (service != nullptr) {
            IAIMPMLGroupingPresets* aimpPresets = nullptr;
            result = CheckResult(
                service->GetActiveStorage(IID_IAIMPMLGroupingPresets, reinterpret_cast<void**>(&aimpPresets)));
            if (result == ActionResultType::OK && aimpPresets != nullptr) {
                presets = gcnew AimpGroupingPresets(aimpPresets);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpGroupingPresets^>(result, presets);
}

ActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpDataStorage^ storage) {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            IAIMPMLDataStorage* s = static_cast<AimpDataStorage^>(storage)->InternalAimpObject;
            result = CheckResult(service->SetActiveStorage(s));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

ActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpGroupingPresets^ preset) {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            IAIMPMLGroupingPresets* s = static_cast<AimpGroupingPresets^>(preset)->InternalAimpObject;
            result = CheckResult(service->SetActiveStorage(s));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return ACTION_RESULT(result);
}

AimpActionResult<IAimpDataStorage^>^ AimpServiceMusicLibrary::GetStorage(int index) {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAimpDataStorage^ storage = nullptr;

    try {
        if (service != nullptr) {
            IAIMPMLDataStorage* aimpStorage = nullptr;
            result = CheckResult(service->GetStorage(index, IID_IAIMPMLDataStorage,
                                                     reinterpret_cast<void**>(&aimpStorage)));
            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpDataStorage(aimpStorage);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpDataStorage^>(result, storage);
}

AimpActionResult<IAimpGroupingPresets^>^ AimpServiceMusicLibrary::GetGroupingPresets(int index) {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAimpGroupingPresets^ presets = nullptr;


    try {
        if (service != nullptr) {
            IAIMPMLGroupingPresets* aimpPresets = nullptr;
            result = CheckResult(service->GetStorage(index, IID_IAIMPMLGroupingPresets,
                                                     reinterpret_cast<void**>(&aimpPresets)));

            if (result == ActionResultType::OK && aimpPresets != nullptr) {
                presets = gcnew AimpGroupingPresets(aimpPresets);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpGroupingPresets^>(result, presets);
}

AimpActionResult<IAimpDataStorage^>^ AimpServiceMusicLibrary::GetStorageById(String^ id) {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* aimpId = nullptr;
    IAimpDataStorage^ storage = nullptr;

    try {
        if (service != nullptr) {
            IAIMPMLDataStorage* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString(id);
            result = CheckResult(
                service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage, reinterpret_cast<void**>(&aimpStorage)));

            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpDataStorage(aimpStorage);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(aimpId);
    }

    return gcnew AimpActionResult<IAimpDataStorage^>(result, storage);
}

AimpActionResult<IAimpGroupingPresets^>^ AimpServiceMusicLibrary::GetGroupingPresetsById(String^ id) {
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* aimpId = nullptr;
    IAimpGroupingPresets^ storage = nullptr;

    try {
        if (service != nullptr) {
            IAIMPMLGroupingPresets* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLGroupingPresets,
                                                         reinterpret_cast<void**>(&aimpStorage)));

            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpGroupingPresets(aimpStorage);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(aimpId);
    }

    return gcnew AimpActionResult<IAimpGroupingPresets^>(result, storage);
}

int AimpServiceMusicLibrary::GetStorageCount() {
    IAIMPServiceMusicLibrary* service = GetAimpService();

    try {
        if (service != nullptr) {
            return service->GetStorageCount();
        }
    }
    finally {
        ReleaseObject(service);
    }

    return 0;
}

IAIMPServiceMusicLibrary* AimpServiceMusicLibrary::GetAimpService() {
    IAIMPServiceMusicLibrary* service = nullptr;
    GetService(IID_IAIMPServiceMusicLibrary, &service);
    return service;
}
