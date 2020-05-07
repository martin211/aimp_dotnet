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

#include "Stdafx.h"
#include "AimpServiceFileInfo.h"
#include "AimpVirtualFile.h"

using namespace AIMP::SDK;

AimpServiceFileInfo::AimpServiceFileInfo(ManagedAimpCore^ core) : BaseAimpService<IAIMPServiceFileInfo>(core)
{
}

ActionResultType AimpServiceFileInfo::GetFileInfoFromFileUri(String^ fileUri, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileInfo* service = GetAimpService();
    IAIMPString* str = nullptr;
    ActionResultType result = ActionResultType::Fail;
    fileInfo = nullptr;

    try
    {
        if (service != nullptr)
        {
            IAIMPFileInfo* fi = nullptr;
            str = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetFileInfoFromFileURI(str, DWORD(fileInfoFlags), fi));

            if (result == ActionResultType::OK && fi != nullptr)
            {
                fileInfo = gcnew AimpFileInfo(fi);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str);
    }

    return result;
}

ActionResultType AimpServiceFileInfo::GetFileInfoFromStream(IAimpStream^ fileStream, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileInfo* service = GetAimpService();
    ActionResultType result = ActionResultType::Fail;
    fileInfo = nullptr;

    try
    {
        if (service != nullptr)
        {
            IAIMPFileInfo* fi = nullptr;
            result = CheckResult(service->GetFileInfoFromStream(
                static_cast<AimpStream^>(fileStream)->InternalAimpObject,
                DWORD(fileInfoFlags),
                fi));

            if (result == ActionResultType::OK && fi != nullptr)
            {
                fileInfo = gcnew AimpFileInfo(fi);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
    }

    return result;
}

ActionResultType AimpServiceFileInfo::GetVirtualFile(String^ fileUri, IAimpVirtualFile^% virtualFile)
{
    IAIMPServiceFileInfo* service = GetAimpService();
    IAIMPString* str = nullptr;
    ActionResultType result = ActionResultType::Fail;
    virtualFile = nullptr;

    try
    {
        if (service != nullptr)
        {
            IAIMPVirtualFile* vf = nullptr;
            str = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetVirtualFile(str, 0, &vf));

            if (result == ActionResultType::OK && vf != nullptr)
            {
                virtualFile = gcnew AimpVirtualFile(vf);
            }
        }
    }
    finally
    {
        ReleaseObject(service);
        ReleaseObject(str); 
    }

    return result;
}

IAIMPServiceFileInfo* AimpServiceFileInfo::GetAimpService()
{
    IAIMPServiceFileInfo* service = nullptr;
    GetService(IID_IAIMPServiceFileInfo, &service);
    return service;
}
