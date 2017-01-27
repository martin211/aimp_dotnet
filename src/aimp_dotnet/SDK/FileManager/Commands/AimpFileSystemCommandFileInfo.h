#pragma once
#include "..\..\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::FileManager::Commands;

        public ref class AimpFileSystemCommandFileInfo : AimpObject<IAIMPFileSystemCommandFileInfo>, IAimpFileSystemCommandFileInfo
        {
        public:
            AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo *aimpObject);

            virtual AimpActionResult GetFileAttrs(String ^file, AimpFileAttributes %attr);

            virtual AimpActionResult GetFileSize(String ^file, long long %size);

            virtual AimpActionResult IsFileExists(String ^file);
        };
    }
}
