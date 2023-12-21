//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpServiceFileStreaming.h"
#include "SDK/Objects/AimpFileStream.h"

StreamResult AimpServiceFileStreaming::CreateStreamForFile(String^ fileName, FileStreamingType flags, long long offset, long long size) {
    IAIMPServiceFileStreaming* service = GetAimpService();
    IAIMPString* str = nullptr;
    IAIMPStream* aimpStream = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAimpStream^ stream = nullptr;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(fileName);
            result = CheckResult(service->CreateStreamForFile(str, static_cast<DWORD>(flags), offset, size, &aimpStream));
            if (result == ActionResultType::OK) {
                IAIMPFileStream* s = (IAIMPFileStream*)aimpStream;
                stream = gcnew AimpFileStream(s);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpStream^>(result, stream);
}

AimpActionResult<CreateStreamResult^>^ AimpServiceFileStreaming::CreateStreamForFileUri(String^ fileUrl) {
    IAIMPServiceFileStreaming* service = GetAimpService();
    IAIMPString* str = nullptr;
    IAIMPStream* aimpStream = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAIMPVirtualFile* vf = nullptr;
    IAimpStream^ stream = nullptr;
    IAimpVirtualFile^ virtualFile = nullptr;

    try {
        if (service != nullptr) {
            str = AimpConverter::ToAimpString(fileUrl);
            result = CheckResult(service->CreateStreamForFileURI(str, &vf, &aimpStream));

            if (result == ActionResultType::OK && aimpStream != nullptr) {
                stream = gcnew AimpFileStream(nullptr);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<CreateStreamResult^>(result, gcnew CreateStreamResult(virtualFile, stream));
}

IAIMPServiceFileStreaming* AimpServiceFileStreaming::GetAimpService() {
    IAIMPServiceFileStreaming* service = nullptr;
    GetService(IID_IAIMPServiceFileStreaming, &service);
    return service;
}
