//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "stdafx.h"
#include "AimpServiceFileURI2.h"

inline AimpActionResult<String^>^ AimpServiceFileURI2::GetScheme(String^ fileUri) {
    IAIMPServiceFileURI2* service = nullptr;
    IAIMPString* file = nullptr;
    IAIMPString* scheme = nullptr;
    ActionResultType result = CheckResult(_core->GetService(IID_IAIMPServiceFileURI2, reinterpret_cast<void**>(&service)));

    try {
        if (service != nullptr) {
            file = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetScheme(file, &scheme));

            if (result == ActionResultType::OK) {
                return gcnew AimpActionResult<String^>(result, AimpConverter::ToManagedString(scheme));
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(file);
        ReleaseObject(scheme);
    }

    return gcnew AimpActionResult<String^>(result);
}