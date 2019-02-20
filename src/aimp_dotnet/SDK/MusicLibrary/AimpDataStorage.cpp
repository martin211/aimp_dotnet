// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorage.h"
#include "AimpGroupingPreset.h"

using namespace AIMP::SDK;
AimpDataStorage::!AimpDataStorage()
{
    _aimpObject->Release();
}

AimpDataStorage::~AimpDataStorage()
{
    this->!AimpDataStorage();
}

AimpActionResult AimpDataStorage::GetProperties(IAIMPPropertyList** properties)
{
    IAIMPPropertyList* prop = nullptr;
    const auto result = CheckResult(InternalAimpObject->QueryInterface(IID_IAIMPPropertyList, reinterpret_cast<void**>(&prop)));
    *properties = prop;
    return result;
}

AimpDataStorage::AimpDataStorage(IAIMPMLDataStorage* aimpDataStorage) : AimpObject(aimpDataStorage)
{
}

String^ AimpDataStorage::Id::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_ID);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

String^ AimpDataStorage::Caption::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            return PropertyListExtension::GetString(properties, AIMPML_DATASTORAGE_PROPID_CAPTION);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return String::Empty;
}

IAimpGroupingPreset^ AimpDataStorage::GroupingPreset::get()
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            IAIMPMLGroupingPreset *preset = nullptr;
            if (PropertyListExtension::GetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET, IID_IAIMPMLGroupingPreset, reinterpret_cast<void**>(&preset)) == AimpActionResult::OK)
            {
                if (preset != nullptr)
                {
                    return gcnew AimpGroupingPreset(preset);
                }
            }
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }

    return nullptr;
}

void AimpDataStorage::GroupingPreset::set(IAimpGroupingPreset ^value)
{
    IAIMPPropertyList* properties = nullptr;
    try
    {
        if (GetProperties(&properties) == AimpActionResult::OK)
        {
            IAIMPMLGroupingPreset* preset = static_cast<AimpGroupingPreset^>(value)->InternalAimpObject;
            PropertyListExtension::SetObject(properties, AIMPML_DATASTORAGE_PROPID_GROUPINGPRESET, preset);
        }
    }
    finally
    {
        if (properties != nullptr)
        {
            properties->Release();
            properties = nullptr;
        }
    }
}
