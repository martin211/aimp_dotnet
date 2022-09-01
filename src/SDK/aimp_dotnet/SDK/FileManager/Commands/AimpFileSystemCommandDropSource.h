//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
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

        public ref class AimpFileSystemCommandDropSource : AimpObject<IAIMPFileSystemCommandDropSource>,
                                                           IAimpFileSystemCommandDropSource {
        public:
            explicit AimpFileSystemCommandDropSource(IAIMPFileSystemCommandDropSource* aimpObject);

            virtual StreamResult CreateStream(String^ fileName);
        };
    }
}