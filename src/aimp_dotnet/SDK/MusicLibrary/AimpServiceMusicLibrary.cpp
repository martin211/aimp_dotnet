// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMusicLibrary.h"
#include "AimpDataStorage.h"
#include "AimpGroupingPresets.h"

using namespace AIMP::SDK;

AimpActionResult AimpServiceMusicLibrary::GetActiveStorage(IAimpDataStorage^% storage)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    storage = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLDataStorage* aimpStorage = nullptr;
            result = CheckResult(
                service->GetActiveStorage(IID_IAIMPMLDataStorage, reinterpret_cast<void**>(&aimpStorage)));
            if (result == AimpActionResult::OK && aimpStorage != nullptr)
            {
                storage = gcnew AimpDataStorage(aimpStorage);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::GetActiveStorage(IAimpGroupingPresets^% presets)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    presets = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLGroupingPresets* aimpPresets = nullptr;
            result = CheckResult(
                service->GetActiveStorage(IID_IAIMPMLGroupingPresets, reinterpret_cast<void**>(&aimpPresets)));
            if (result == AimpActionResult::OK && aimpPresets != nullptr)
            {
                presets = gcnew AimpGroupingPresets(aimpPresets);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpDataStorage^ storage)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        // TODO complete it
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLGroupingPresets* storage;
            //result = CheckResult(service->SetActiveStorage(IID_IAIMPMLGroupingPresets));
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::SetActiveStorage(IAimpGroupingPresets^ preset)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        // TODO complete it
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLGroupingPresets* storage;
            //result = CheckResult(service->SetActiveStorage(IID_IAIMPMLGroupingPresets));
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::GetStorage(int index, IAimpDataStorage^% storage)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    storage = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLDataStorage* aimpStorage = nullptr;
            result = CheckResult(service->GetStorage(index, IID_IAIMPMLDataStorage,
                                                     reinterpret_cast<void**>(&aimpStorage)));
            if (result == AimpActionResult::OK && aimpStorage != nullptr)
            {
                storage = gcnew AimpDataStorage(aimpStorage);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::GetStorage(int index, IAimpGroupingPresets^% storage)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLGroupingPresets* aimpPresets = nullptr;
            result = CheckResult(service->GetStorage(index, IID_IAIMPMLGroupingPresets,
                                                     reinterpret_cast<void**>(&aimpPresets)));

            if (result == AimpActionResult::OK && aimpPresets != nullptr)
            {
                storage = gcnew AimpGroupingPresets(aimpPresets);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::GetStorageById(String^ id, IAimpDataStorage^% storage)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* aimpId = nullptr;
    storage = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLDataStorage* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString(id);
            result = CheckResult(
                service->GetStorageByID(aimpId, IID_IAIMPMLDataStorage, reinterpret_cast<void**>(&aimpStorage)));

            if (result == AimpActionResult::OK && aimpStorage != nullptr)
            {
                storage = gcnew AimpDataStorage(aimpStorage);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            aimpId->Release();
        }
    }

    return result;
}

AimpActionResult AimpServiceMusicLibrary::GetStorageById(String^ id, IAimpGroupingPresets^% storage)
{
    IAIMPServiceMusicLibrary* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* aimpId = nullptr;
    storage = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPMLGroupingPresets* aimpStorage = nullptr;
            aimpId = AimpConverter::ToAimpString(id);
            result = CheckResult(service->GetStorageByID(aimpId, IID_IAIMPMLGroupingPresets,
                                                         reinterpret_cast<void**>(&aimpStorage)));

            if (result == AimpActionResult::OK && aimpStorage != nullptr)
            {
                storage = gcnew AimpGroupingPresets(aimpStorage);
            }
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            aimpId->Release();
        }
    }

    return result;
}

int AimpServiceMusicLibrary::GetStorageCount()
{
    IAIMPServiceMusicLibrary* service = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMusicLibrary, &service) == AimpActionResult::OK && service != nullptr)
        {
            return service->GetStorageCount();
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }
    }

    return 0;
}
