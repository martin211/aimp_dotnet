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

using namespace AIMP::SDK;
AimpServiceFileInfo::AimpServiceFileInfo(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileInfo>(core)
{

}

AimpActionResult AimpServiceFileInfo::GetFileInfoFromFileUri(String ^fileUri, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo ^%fileInfo)
{
    IAIMPServiceFileInfo *service = NULL;
    IAIMPString *str = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceFileInfo, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                IAIMPFileInfo *fi = NULL;
                str = AimpConverter::ToAimpString(fileUri);
                result = CheckResult(service->GetFileInfoFromFileURI(str, (DWORD)fileInfoFlags, fi));

                if (result == AimpActionResult::Ok)
                {
                    fileInfo = gcnew AIMP::SDK::AimpFileInfo(fi);
                }
            }
        }

        return result;
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }
}

AimpActionResult AimpServiceFileInfo::GetFileInfoFromStream(IAimpStream ^fileStream, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo ^% fileInfo)
{
    fileInfo = nullptr;
    return AimpActionResult::NotImplemented;
}

AimpActionResult AimpServiceFileInfo::GetVirtualFile(String ^fileUri, IAimpVirtualFile ^%virtualFile)
{
    IAIMPServiceFileInfo *service = NULL;
    IAIMPString *str = NULL;
    AimpActionResult result = AimpActionResult::Fail;

    try
    {
        if (GetService(IID_IAIMPServiceFileInfo, &service) == AimpActionResult::Ok)
        {
            if (service != NULL)
            {
                IAIMPVirtualFile *vf;
                str = AimpConverter::ToAimpString(fileUri);
                result = CheckResult(service->GetVirtualFile(str, 0, &vf));

                if (result == AimpActionResult::Ok)
                {
                    virtualFile = gcnew AIMP::SDK::AimpVirtualFile(vf);
                }
            }
        }

        return result;
    }
    finally
    {
        if (service != NULL)
        {
            service->Release();
            service = NULL;
        }

        if (str != NULL)
        {
            str->Release();
            str = NULL;
        }
    }
}
