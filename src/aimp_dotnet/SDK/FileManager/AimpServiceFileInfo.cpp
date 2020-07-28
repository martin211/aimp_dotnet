// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpServiceFileInfo.h"
#include "AimpVirtualFile.h"

using namespace AIMP::SDK;

AimpServiceFileInfo::AimpServiceFileInfo(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileInfo>(core) {
}

FileInfoResult AimpServiceFileInfo::GetFileInfoFromFileUri(String^ fileUri, ServiceFileInfoFlags fileInfoFlags) {
    IAIMPServiceFileInfo* service = GetAimpService();
    IAIMPString* str = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAimpFileInfo^ fileInfo = nullptr;

    try {
        if (service != nullptr) {
            IAIMPFileInfo* fi = nullptr;
            str = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetFileInfoFromFileURI(str, DWORD(fileInfoFlags), fi));

            if (result == ActionResultType::OK && fi != nullptr) {
                fileInfo = gcnew AimpFileInfo(fi);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpFileInfo^>(result, fileInfo);
}

FileInfoResult AimpServiceFileInfo::GetFileInfoFromStream(IAimpStream^ fileStream, ServiceFileInfoFlags fileInfoFlags) {
    IAIMPServiceFileInfo* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    IAimpFileInfo^ fileInfo = nullptr;

    try {
        if (service != nullptr) {
            IAIMPFileInfo* fi = nullptr;
            result = CheckResult(service->GetFileInfoFromStream(
                static_cast<AimpStream^>(fileStream)->InternalAimpObject,
                DWORD(fileInfoFlags),
                fi));

            if (result == ActionResultType::OK && fi != nullptr) {
                fileInfo = gcnew AimpFileInfo(fi);
            }
        }
    }
    finally {
        ReleaseObject(service);
    }

    return gcnew AimpActionResult<IAimpFileInfo^>(result, fileInfo);
}

VirtualFileResult AimpServiceFileInfo::GetVirtualFile(String^ fileUri) {
    IAIMPServiceFileInfo* service = GetAimpService();
    IAIMPString* str = nullptr;
    ActionResultType result = ActionResultType::Fail;
    IAimpVirtualFile^ virtualFile = nullptr;

    try {
        if (service != nullptr) {
            IAIMPVirtualFile* vf = nullptr;
            str = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetVirtualFile(str, 0, &vf));

            if (result == ActionResultType::OK && vf != nullptr) {
                virtualFile = gcnew AimpVirtualFile(vf);
            }
        }
    }
    finally {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return gcnew AimpActionResult<IAimpVirtualFile^>(result, virtualFile);
}

IAIMPServiceFileInfo* AimpServiceFileInfo::GetAimpService() {
    IAIMPServiceFileInfo* service = nullptr;
    GetService(IID_IAIMPServiceFileInfo, &service);
    return service;
}
