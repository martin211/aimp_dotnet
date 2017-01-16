#pragma once
#include "..\..\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;

        public ref class AimpFileSystemCommandFileInfo : AimpObject<IAIMPFileSystemCommandFileInfo>, IAimpFileSystemCommandFileInfo
        {
        public:
            AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo *aimpObject) : AimpObject(aimpObject)
            {}

            virtual AimpActionResult GetFileAttrs(String ^file, AimpFileAttributes %attr)
            {
                IAIMPString *str = AimpExtension::GetAimpString(file);
                try
                {
                    TAIMPFileAttributes *fattr = NULL;
                    AimpActionResult result = CheckResult(_aimpObject->GetFileAttrs(str, fattr));
                    return result;
                }
                finally
                {
                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }
            }

            virtual AimpActionResult GetFileSize(String ^file, long long %size)
            {
                IAIMPString *str = NULL;

                try
                {
                    str = AimpExtension::GetAimpString(file);
                    INT64 *fSize = 0;
                    AimpActionResult result = CheckResult(_aimpObject->GetFileSize(str, fSize));
                    if (result == AimpActionResult::Ok)
                    {
                        size = (long long)fSize;
                    }

                    return result;
                }
                finally
                {
                    if (str != NULL)
                    {
                        str->Release();
                        str = NULL;
                    }
                }
            }

            virtual AimpActionResult IsFileExists(String ^file)
            {
                IAIMPString *str = NULL;
                try
                {
                    str = AimpExtension::GetAimpString(file);
                    return CheckResult(_aimpObject->IsFileExists(str));
                }
                finally
                {
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
