//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMusicLibrary.h"

#include "AimpLocalDataStorage.h"
#include "DataStorage/AimpDataStorage.h"
#include "DataStorage/AimpDataStorage2.h"

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

//AimpActionResult<IAimpDataStorage2^>^ AimpServiceMusicLibrary::GetStorageById(String^ id) {
//    IAIMPServiceMusicLibrary* service = GetAimpService();
//    ActionResultType result = ActionResultType::Fail;
//    IAIMPString* aimpId = nullptr;
//    IAimpDataStorage2^ storage = nullptr;
//
//    try {
//        if (service != nullptr) {
//            IAIMPMLDataStorage2* aimpStorage = nullptr;
//            aimpId = AimpConverter::ToAimpString(id);
//            result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage2, reinterpret_cast<void**>(&aimpStorage)));
//
//            if (result == ActionResultType::OK && aimpStorage != nullptr) {
//                storage = gcnew AimpDataStorage(aimpStorage);
//            }
//        }
//    }
//    finally {
//        ReleaseObject(service);
//        ReleaseObject(aimpId);
//    }
//
//    return gcnew AimpActionResult<IAimpDataStorage2^>(result, storage);
//}

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

generic <class TAimpDataStorage>
AimpActionResult<TAimpDataStorage>^ AimpServiceMusicLibrary::GetStorageById(String^ id) {
    const auto t = TAimpDataStorage::typeid;
    IAIMPServiceMusicLibrary* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* aimpId = nullptr;

    if (t == IAimpDataStorage::typeid) {
        try {
            IAimpDataStorage^ storage = nullptr;
            IAIMPMLDataStorage* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage, reinterpret_cast<void**>(&aimpStorage)));
            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpDataStorage(aimpStorage);
            }

            return gcnew AimpActionResult<TAimpDataStorage>(result, safe_cast<TAimpDataStorage>(storage));
        }
        finally {
            ReleaseObject(service);
            ReleaseObject(aimpId);
        }
    }

    if (t == IAimpDataStorage2::typeid) {
        try {
            IAimpDataStorage2^ storage = nullptr;
            IAIMPMLDataStorage2* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage2, reinterpret_cast<void**>(&aimpStorage)));

            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpDataStorage2(aimpStorage);
            }

            return gcnew AimpActionResult<TAimpDataStorage>(result, safe_cast<TAimpDataStorage>(storage));
        }
        finally {
            ReleaseObject(service);
            ReleaseObject(aimpId);
        }
    }

    if (t == IAimpLocalDataStorage::typeid) {
        try {
            IAimpLocalDataStorage^ storage = nullptr;
            IAIMPMLDataStorage2* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString("TAIMPMLLocalDataStorage");
            result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage2, reinterpret_cast<void**>(&aimpStorage)));

            if (result == ActionResultType::OK && aimpStorage != nullptr) {
                storage = gcnew AimpLocalDataStorage(aimpStorage);
            }

            return gcnew AimpActionResult<TAimpDataStorage>(result, safe_cast<TAimpDataStorage>(storage));
        }
        finally {
            ReleaseObject(service);
            ReleaseObject(aimpId);
        }
    }

    return gcnew AimpActionResult<TAimpDataStorage>(result);
}
