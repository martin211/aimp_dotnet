//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpFileSystemCommandDropSource.h"

using namespace AIMP::SDK;

AimpFileSystemCommandDropSource::
AimpFileSystemCommandDropSource(IAIMPFileSystemCommandDropSource* aimpObject) : AimpObject(aimpObject) {
}

StreamResult AimpFileSystemCommandDropSource::CreateStream(String^ fileName) {
    auto str = AimpConverter::ToAimpString(fileName);
    IAimpStream^ stream = nullptr;
    ActionResultType res = ActionResultType::Fail;

    try {
        IAIMPStream* aimpStream = nullptr;
        res = CheckResult(InternalAimpObject->CreateStream(str, reinterpret_cast<IAIMPStream**>(&aimpStream)));
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
