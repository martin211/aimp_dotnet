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

#pragma once
#include "SDK\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::FileManager::Commands;
        using namespace AIMP::SDK::Objects;

        public ref class AimpFileSystemCommandFileInfo : AimpObject<IAIMPFileSystemCommandFileInfo>, IAimpFileSystemCommandFileInfo
        {
        public:
            AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo *aimpObject);

            virtual AimpActionResult GetFileAttrs(IAimpString ^file, AimpFileAttributes %attr);

            virtual AimpActionResult GetFileSize(IAimpString ^file, long long %size);

            virtual AimpActionResult IsFileExists(IAimpString ^file);
        };
    }
}
