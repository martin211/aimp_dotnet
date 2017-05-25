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
#include "MUIManager.h"


AIMP::SDK::AimpMIUManager::AimpMIUManager(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceMUI>(core)
{
}

AIMP::SDK::AimpMIUManager::~AimpMIUManager()
{
}

System::String^ AIMP::SDK::AimpMIUManager::GetName()
{
    IAIMPString *str = NULL;
    IAIMPServiceMUI* service = NULL;
    try
    {
        if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                service->GetName(&str);

                if (str != NULL)
                    return gcnew String(str->GetData());
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return String::Empty;
}

System::String^ AIMP::SDK::AimpMIUManager::GetValue(String^ key)
{
    IAIMPString *str = NULL;
    IAIMPServiceMUI* service = NULL;
    try
    {
        if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::Ok)
        {
            if (service == NULL)
            {
                return String::Empty;
            }

            IAIMPString* strKey = AimpConverter::ToAimpString(key);

            if (service->GetValue(strKey, &str) == S_OK)
            {
                strKey->Release();

                if (str == NULL)
                {
                    return String::Empty;
                }

                return gcnew String(str->GetData());
            }
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return String::Empty;
}

System::String^ AIMP::SDK::AimpMIUManager::GetValuePart(String^ key, int index)
{
    IAIMPString *str = NULL;
    IAIMPServiceMUI* service = NULL;
    try
    {
        if (GetService(IID_IAIMPServiceMUI, &service) == AimpActionResult::Ok)
        {
            if (service == NULL)
                return nullptr;

            IAIMPString* strKey = AimpConverter::ToAimpString(key);
            service->GetValuePart(strKey, index, &str);

            strKey->Release();

            if (str == NULL)
            {
                return String::Empty;
            }

            return gcnew String(str->GetData());
        }
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }

    return String::Empty;
}
