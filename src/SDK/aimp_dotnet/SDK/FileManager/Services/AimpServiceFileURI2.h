//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpServiceFileURI.h"
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        public ref class AimpServiceFileURI2 :
            public AimpServiceFileURI,
            public IAimpServiceFileURI2 {
        public:
            explicit AimpServiceFileURI2(ManagedAimpCore^ core)
                : AimpServiceFileURI(core) {
            }

            virtual AimpActionResult<String^>^ GetScheme(String^ fileUri);
        };
    }
}
