//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "DataStorage/AimpDataStorage2.h"

namespace AIMP {
    namespace SDK {

        public ref class AimpLocalDataStorage : public AimpDataStorage2, public IAimpLocalDataStorage {
        public:
            explicit AimpLocalDataStorage(IAIMPMLDataStorage2* obj);
        };
    }
}
