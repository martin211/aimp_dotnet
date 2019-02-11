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
#include "AimpServiceFileFormats.h"

using namespace AIMP::SDK;

AimpServiceFileFormats::AimpServiceFileFormats(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileFormats>(core)
{ }

AimpActionResult AimpServiceFileFormats::GetFormats(FileFormats flags, String^% formats)
{
    IAIMPServiceFileFormats* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* str = nullptr;
    formats = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileFormats, &service) == AimpActionResult::OK && service != nullptr)
        {
            result = CheckResult(service->GetFormats(DWORD(flags), &str));

            if (result == AimpActionResult::OK)
            {
                formats = AimpConverter::ToManagedString(str);
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

    return result;
}

AimpActionResult AimpServiceFileFormats::IsSupported(String^ fileName, FileFormats flags)
{
    IAIMPServiceFileFormats* service = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString* str = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileFormats, &service) == AimpActionResult::OK && service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileName);
            result = CheckResult(service->IsSupported(str, DWORD(flags)));
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

    return result;
}
