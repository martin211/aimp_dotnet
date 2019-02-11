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

#include "Stdafx.h"
#include "AimpServiceFileInfo.h"
#include "AimpVirtualFile.h"

using namespace AIMP::SDK;
AimpServiceFileInfo::AimpServiceFileInfo(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileInfo>(core)
{

}

AimpActionResult AimpServiceFileInfo::GetFileInfoFromFileUri(String^ fileUri, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo^% fileInfo)
{
    IAIMPServiceFileInfo* service = nullptr;
    IAIMPString* str = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    fileInfo = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileInfo, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPFileInfo* fi = nullptr;
            str = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetFileInfoFromFileURI(str, DWORD(fileInfoFlags), fi));

            if (result == AimpActionResult::OK)
            {
                fileInfo = gcnew AimpFileInfo(fi);
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

AimpActionResult AimpServiceFileInfo::GetFileInfoFromStream(IAimpStream^ fileStream, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo^% fileInfo)
{
    // TODO Complete it
    fileInfo = nullptr;
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpServiceFileInfo::GetVirtualFile(String^ fileUri, IAimpVirtualFile^% virtualFile)
{
    IAIMPServiceFileInfo* service = nullptr;
    IAIMPString* str = nullptr;
    AimpActionResult result = AimpActionResult::Fail;
    virtualFile = nullptr;

    try
    {
        if (GetService(IID_IAIMPServiceFileInfo, &service) == AimpActionResult::OK && service != nullptr)
        {
            IAIMPVirtualFile* vf;
            str = AimpConverter::ToAimpString(fileUri);
            result = CheckResult(service->GetVirtualFile(str, 0, &vf));

            if (result == AimpActionResult::OK && vf != nullptr)
            {
                virtualFile = gcnew AimpVirtualFile(vf);
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
