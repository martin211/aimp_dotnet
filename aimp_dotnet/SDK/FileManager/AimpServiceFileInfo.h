#pragma once
#include "..\BaseManager.h"
#include "AimpFileInfo.h"
#include "AimpVirtualFile.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace System::IO;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpServiceFileInfo : public AimpBaseManager<IAIMPServiceFileInfo>, public IAimpServiceFileInfo
        {
        public:
            AimpServiceFileInfo(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileInfo>(core)
            {}

            virtual AimpActionResult GetFileInfoFromFileUri(String ^fileUri, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo ^%fileInfo)
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
                            str = AimpExtension::GetAimpString(fileUri);
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

            virtual AimpActionResult GetFileInfoFromStream(IAimpStream ^fileStream, ServiceFileInfoFlags fileInfoFlags, IAimpFileInfo ^% fileInfo)
            {
                fileInfo = nullptr;
                return AimpActionResult::NotImplemented;
            }

            virtual AimpActionResult GetVirtualFile(String ^fileUri, IAimpVirtualFile ^%virtualFile)
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
                            str = AimpExtension::GetAimpString(fileUri);
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
        };
    }
}