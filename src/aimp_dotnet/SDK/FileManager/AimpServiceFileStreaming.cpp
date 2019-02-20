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

#include "stdafx.h"
#include "AimpServiceFileStreaming.h"

AimpActionResult AimpServiceFileStreaming::CreateStreamForFile(String^ fileName, FileStreamingType flags, long long offset, long long size, IAimpStream^% stream)
{
    IAIMPServiceFileStreaming* service = nullptr;
    IAIMPString* str = nullptr;
    IAIMPStream* aimpStream = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    stream = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileStreaming, &service) == AimpActionResult::OK && service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileName);
            result = CheckResult(service->CreateStreamForFile(str, DWORD(flags), offset, size, &aimpStream));

            if (result == AimpActionResult::OK)
            {
                stream = gcnew AimpStream(aimpStream);
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

AimpActionResult AimpServiceFileStreaming::CreateStreamForFileUri(String^ fileUrl, IAimpVirtualFile^% virtualFile, IAimpStream^% stream)
{
    IAIMPServiceFileStreaming* service = nullptr;
    IAIMPString* str = nullptr;
    IAIMPStream* aimpStream = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    IAIMPVirtualFile* vf = nullptr;
    stream = nullptr;
    virtualFile = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileStreaming, &service) == AimpActionResult::OK && service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileUrl);
            result = CheckResult(service->CreateStreamForFileURI(str, &vf, &aimpStream));

            if (result == AimpActionResult::OK && aimpStream != nullptr)
            {
                stream = gcnew AimpStream(aimpStream);
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
