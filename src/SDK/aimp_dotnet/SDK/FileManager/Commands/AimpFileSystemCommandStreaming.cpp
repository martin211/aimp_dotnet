//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK;

AimpFileSystemCommandStreaming::
AimpFileSystemCommandStreaming(IAIMPFileSystemCommandStreaming* aimpObject) : AimpObject(aimpObject) {
}

StreamResult AimpFileSystemCommandStreaming::CreateStream(String^ fileName, FileStreamingType flags, long long offset,
                                                          long long size) {
    auto str = AimpConverter::ToAimpString(fileName);
    ActionResultType res = ActionResultType::Fail;
    IAimpStream^ stream = nullptr;

    try {
        IAIMPStream* aimpStream = nullptr;
        res = CheckResult(
            InternalAimpObject->CreateStream(str, offset, size, DWORD(flags),
                                             reinterpret_cast<IAIMPStream**>(&aimpStream)));
        if (res == ActionResultType::OK && aimpStream != nullptr) {
            stream = gcnew AimpStream(aimpStream);
        }
    }
    finally {
        if (str != nullptr) {
            str->Release();
            str = nullptr;
        }
    }


    return gcnew AimpActionResult<IAimpStream^>(res, stream);
}
