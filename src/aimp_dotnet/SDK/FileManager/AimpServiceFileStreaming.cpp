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

#include "stdafx.h"
#include "AimpServiceFileStreaming.h"

StreamResult AimpServiceFileStreaming::CreateStreamForFile(String^ fileName, FileStreamingType flags, long long offset, long long size)
{
    IAIMPServiceFileStreaming* service = GetAimpService();
    IAIMPString* str = nullptr;
    IAIMPStream* aimpStream = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAimpStream^ stream = nullptr;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileName);
            result = CheckResult(service->CreateStreamForFile(str, DWORD(flags), offset, size, &aimpStream));

            if (result == ActionResultType::OK)
            {
                stream = gcnew AimpStream(aimpStream);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpStream^>(result, stream);
}

AimpActionResult<CeateStreamResult^>^ AimpServiceFileStreaming::CreateStreamForFileUri(String^ fileUrl)
{
    IAIMPServiceFileStreaming* service = GetAimpService();
    IAIMPString* str = nullptr;
    IAIMPStream* aimpStream = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAIMPVirtualFile* vf = nullptr;
    IAimpStream^ stream = nullptr;
    IAimpVirtualFile^  virtualFile = nullptr;

    try
    {
        if (service != nullptr)
        {
            str = AimpConverter::ToAimpString(fileUrl);
            result = CheckResult(service->CreateStreamForFileURI(str, &vf, &aimpStream));

            if (result == ActionResultType::OK && aimpStream != nullptr)
            {
                stream = gcnew AimpStream(aimpStream);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<CeateStreamResult^>(result, gcnew CeateStreamResult(virtualFile, stream));
}

IAIMPServiceFileStreaming* AimpServiceFileStreaming::GetAimpService()
{
    IAIMPServiceFileStreaming* service = nullptr;
    GetService(IID_IAIMPServiceFileStreaming, &service);
    return service;
}
