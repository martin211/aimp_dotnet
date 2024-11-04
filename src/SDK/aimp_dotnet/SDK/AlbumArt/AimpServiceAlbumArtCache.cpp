//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceAlbumArtCache.h"

#include "SDK/Objects/AimpImageContainer.h"

using namespace AIMP::SDK;

AimpServiceAlbumArtCache::AimpServiceAlbumArtCache(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceAlbumArtCache>(core) {
}

AimpActionResult^ AimpServiceAlbumArtCache::Flush() {
    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            result = CheckResult(service->Flush());
        }
    }
    finally {
        ReleaseObject(service);
    }

    return GetResult(result);
}

AimpActionResult<IAimpImageContainer^>^ AimpServiceAlbumArtCache::Get(String^ key) {
    auto service = GetAimpService();
    auto str = AimpConverter::ToAimpString(key);
    IAIMPImageContainer* container = nullptr;

    try {
        if (service != nullptr) {
            ActionResultType result = CheckResult(service->Get(str, &container));
            if (result == ActionResultType::OK && container != nullptr) {
                return gcnew AimpActionResult<IAimpImageContainer^>(result, gcnew AimpImageContainer(container));
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpImageContainer^>();
}

AimpActionResult^ AimpServiceAlbumArtCache::Put(String^ key, IAimpImageContainer^ image) {
    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    auto str = AimpConverter::ToAimpString(key);

    try {
        if (service != nullptr) {
            auto container = safe_cast<AimpImageContainer^>(image)->InternalAimpObject;
            result = CheckResult(service->Put(str, &container));
            return gcnew AimpActionResult(result);
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult(result);
}

AimpActionResult^ AimpServiceAlbumArtCache::Remove(String^ key) {
    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    auto str = AimpConverter::ToAimpString(key);

    try {
        if (service != nullptr) {
            result = CheckResult(service->Remove(str));
            return gcnew AimpActionResult(result);
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult(result);
}

AimpActionResult<Tuple<int, int>^>^ AimpServiceAlbumArtCache::Stat() {
    auto service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            INT64 size = 0;
            DWORD count = 0;

            result = CheckResult(service->Stat(&size, &count));

            return gcnew AimpActionResult<Tuple<int, int>^>(result, gcnew Tuple<int, int>(size, count));
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<Tuple<int, int>^>(result);
}

IAIMPServiceAlbumArtCache* AimpServiceAlbumArtCache::GetAimpService() {
    IAIMPServiceAlbumArtCache* service = nullptr;
    GetService(IID_IAIMPServiceAlbumArtCache, &service);
    return service;
}
