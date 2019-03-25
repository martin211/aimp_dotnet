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

#pragma once
#include "SDK\AimpObject.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace FileManager;
        using namespace Commands;
        using namespace Objects;

        public ref class AimpFileSystemCommandFileInfo : AimpObject<IAIMPFileSystemCommandFileInfo>,
                                                         IAimpFileSystemCommandFileInfo
        {
        public:
            explicit AimpFileSystemCommandFileInfo(IAIMPFileSystemCommandFileInfo* aimpObject);

            virtual AimpActionResult GetFileSize(String^ file, long long% size);

            virtual AimpActionResult IsFileExists(String^ file);

            virtual AimpActionResult GetFileAttrs(String^ fileName, AimpFileAttributes% attr);
        };
    }
}
