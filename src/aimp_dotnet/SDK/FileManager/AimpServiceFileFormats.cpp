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
                    formats = AimpExtension::GetString(str);
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
                str = AimpExtension::GetAimpString(fileName);
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
