/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "AimpServiceFileFormats.h"

using namespace AIMP::SDK;

AimpServiceFileFormats::AimpServiceFileFormats(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileFormats>(core)
{ }

AimpActionResult AimpServiceFileFormats::GetFormats(FileFormats flags, String ^% formats)
{
    IAIMPServiceFileFormats *service = NULL;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString *str = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceFileFormats, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                result = CheckResult(service->GetFormats((DWORD)flags, &str));

                if (result == AimpActionResult::Ok)
                {
                    formats = AimpConverter::ToManagedString(str);
                }
            }
        }

        return result;
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
}

AimpActionResult AimpServiceFileFormats::IsSupported(String ^fileName, FileFormats flags)
{
    IAIMPServiceFileFormats *service = NULL;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPString *str = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceFileFormats, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                str = AimpConverter::ToAimpString(fileName);
                result = CheckResult(service->IsSupported(str, (DWORD)flags));
            }
        }

        return result;
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
}
