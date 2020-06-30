// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceFileFormats.h"

using namespace AIMP::SDK;

AimpServiceFileFormats::AimpServiceFileFormats(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileFormats>(core)
{
}

StringResult AimpServiceFileFormats::GetFormats(FileFormats flags)
{
    IAIMPServiceFileFormats* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* str = nullptr;
    String^ formats = nullptr;

    try
    {
        if (service != nullptr)
        {
            result = CheckResult(service->GetFormats(DWORD(flags), &str));

            if (result == ActionResultType::OK)
            {
                formats = AimpConverter::ToManagedString(str);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<String^>(result, formats);
}

VoidResult AimpServiceFileFormats::IsSupported(String^ fileName, FileFormats flags)
{
    IAIMPServiceFileFormats* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* str = nullptr;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileName);
            result = CheckResult(service->IsSupported(str, DWORD(flags)));
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return ACTION_RESULT(result);
}

IAIMPServiceFileFormats* AimpServiceFileFormats::GetAimpService()
{
    IAIMPServiceFileFormats* service = nullptr;
    GetService(IID_IAIMPServiceFileFormats, &service);
    return service;
}
