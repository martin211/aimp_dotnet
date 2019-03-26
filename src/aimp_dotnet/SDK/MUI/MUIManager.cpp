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
#include "MUIManager.h"

AimpMIUManager::AimpMIUManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMUI>(core)
{
}

AimpMIUManager::~AimpMIUManager()
{
}

String^ AimpMIUManager::GetName()
{
    IAIMPString* str = nullptr;
    IAIMPServiceMUI* service = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::OK && service != nullptr)
        {
            service->GetName(&str);

            if (str != nullptr)
            {
                return gcnew String(str->GetData());
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

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return String::Empty;
}

String^ AimpMIUManager::GetValue(String^ key)
{
    IAIMPString* str = nullptr;
    IAIMPServiceMUI* service = nullptr;
    try
    {
        if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::OK && service != nullptr)
        {
            auto strKey = AimpConverter::ToAimpString(key);

            if (service->GetValue(strKey, &str) == S_OK)
            {
                strKey->Release();
                strKey = nullptr;

                if (str == nullptr)
                {
                    return String::Empty;
                }

                return gcnew String(str->GetData());
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

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return String::Empty;
}

String^ AimpMIUManager::GetValuePart(String^ key, int index)
{
    IAIMPString* str = nullptr;
    IAIMPServiceMUI* service = nullptr;
    try
    {
        if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::OK && service == nullptr)
        {
            auto strKey = AimpConverter::ToAimpString(key);
            service->GetValuePart(strKey, index, &str);

            strKey->Release();
            strKey = nullptr;

            if (str == nullptr)
            {
                return String::Empty;
            }

            return gcnew String(str->GetData());
        }
    }
    finally
    {
        if (service != nullptr)
        {
            service->Release();
            service = nullptr;
        }

        if (str != nullptr)
        {
            str->Release();
            str = nullptr;
        }
    }

    return String::Empty;
}
