#pragma once
#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpServiceFileFormats : public AimpBaseManager<IAIMPServiceFileFormats>, public IAimpServiceFileFormats
        {
        public:
            explicit AimpServiceFileFormats(ManagedAimpCore^ core) : AimpBaseManager<IAIMPServiceFileFormats>(core)
            {}

            virtual AimpActionResult GetFormats(FileFormats flags, String ^% formats)
            {
                IAIMPServiceFileFormats *service = NULL;
                AimpActionResult result = AimpActionResult::Fail;
                IAIMPString *str = NULL;

                try
                {
                    if (GetService(IID_IAIMPServiceFileFormats, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            result = CheckResult(service->GetFormats((DWORD)flags, &str));

                            if (result == AimpActionResult::Ok)
                            {
                                formats = AimpExtension::GetString(str);
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

            virtual AimpActionResult IsSupported(String ^fileName, FileFormats flags)
            {
                IAIMPServiceFileFormats *service = NULL;
                AimpActionResult result = AimpActionResult::Fail;
                IAIMPString *str = NULL;

                try
                {
                    if (GetService(IID_IAIMPServiceFileFormats, &service) == AimpActionResult::Ok)
                    {
                        if (service != NULL)
                        {
                            str = AimpExtension::GetAimpString(fileName);
                            result = CheckResult(service->IsSupported(str, (DWORD)flags));
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