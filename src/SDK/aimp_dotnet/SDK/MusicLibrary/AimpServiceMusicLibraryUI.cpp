//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceMusicLibraryUI.h"
#include "AimpFileList.h"
#include "DataFilter/AimpDataFilter.h"

using namespace AIMP::SDK;

AimpServiceMusicLibraryUI::
AimpServiceMusicLibraryUI(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceMusicLibraryUI>(core) {
}

AimpActionResult<IAimpFileList^>^ AimpServiceMusicLibraryUI::GetFiles(FilesType flags) {
    IAimpFileList^ list = nullptr;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            IAIMPMLFileList* l = nullptr;
            result = CheckResult(service->GetFiles(static_cast<int>(flags), &l));

            if (result == ActionResultType::OK && l != nullptr) {
                list = gcnew AimpFileList(l);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpFileList^>(result, list);
}

AimpActionResult<IAimpDataFilter^>^ AimpServiceMusicLibraryUI::GetGroupingFilter() {
    IAimpDataFilter^ filter = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();

    try {
        if (service != nullptr) {
            IAIMPMLDataFilter* f = nullptr;
            result = CheckResult(service->GetGroupingFilter(&f));

            if (result == ActionResultType::OK && f != nullptr) {
                filter = gcnew AimpDataFilter(f);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpDataFilter^>(result, filter);
}

StringResult AimpServiceMusicLibraryUI::GetGroupingFilterPath() {
    String^ path = String::Empty;
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;

    try {
        if (service != nullptr) {
            IAIMPString* str = nullptr;
            result = CheckResult(service->GetGroupingFilterPath(&str));

            if (result == ActionResultType::OK && str != nullptr) {
                path = AimpConverter::ToManagedString(str);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return STRING_RESULT(result, path);
}

ActionResult AimpServiceMusicLibraryUI::SetGroupingFilterPath(String^ path) {
    IAIMPServiceMusicLibraryUI* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAIMPString* strPath = nullptr;

    try {
        if (service != nullptr) {
            strPath = AimpConverter::ToAimpString(path);
            result = CheckResult(service->SetGroupingFilterPath(strPath));
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(strPath);
    }

    return ACTION_RESULT(result);
}

IAIMPServiceMusicLibraryUI* AimpServiceMusicLibraryUI::GetAimpService() {
    IAIMPServiceMusicLibraryUI* service = nullptr;
    GetService(IID_IAIMPServiceMusicLibraryUI, &service);
    return service;
}
