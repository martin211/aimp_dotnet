/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "stdafx.h"
#include "AimpServiceFileStreaming.h"

AimpActionResult AimpServiceFileStreaming::CreateStreamForFile(String ^fileName, FileStreamingType flags, long long ofset, long long size, IAimpStream ^%stream)
{
    IAIMPServiceFileStreaming *service = NULL;
    IAIMPString *str = NULL;
    IAIMPStream *aimpStream = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceFileStreaming, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                str = AimpConverter::ToAimpString(fileName);
                result = CheckResult(service->CreateStreamForFile(str, (DWORD)flags, ofset, size, &aimpStream));

                if (result == AimpActionResult::Ok)
                {
                    stream = gcnew AimpStream(aimpStream);
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

AimpActionResult AimpServiceFileStreaming::CreateStreamForFileUri(String ^fileUrl, IAimpVirtualFile ^%virtualFile, IAimpStream ^%stream)
{
    IAIMPServiceFileStreaming *service = NULL;
    IAIMPString *str = NULL;
    IAIMPStream *aimpStream = NULL;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPVirtualFile *vf = NULL;

    try
    {
        if (GetService(IID_IAIMPServiceFileStreaming, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                str = AimpConverter::ToAimpString(fileUrl);
                result = CheckResult(service->CreateStreamForFileURI(str, &vf, &aimpStream));

                if (result == AimpActionResult::Ok)
                {
                    stream = gcnew AimpStream(aimpStream);
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
