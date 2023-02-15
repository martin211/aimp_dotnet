//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK\AimpObject.h"

namespace AIMP {
    namespace SDK {
        using namespace System;
        using namespace FileManager;
        using namespace Commands;

        public ref class AimpFileSystemCommandFileInfo : AimpObject<IAIMPFileSystemCommandFileInfo>,
                                                         IAimpFileSystemCommandFileInfo {
        public:
            explicit AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo* aimpObject);

            virtual LongResult GetFileSize(String^ file);

            virtual ActionResult IsFileExists(String^ file);

            virtual AimpActionResult<AimpFileAttributes>^ GetFileAttrs(String^ fileName);
        };
    }
}
