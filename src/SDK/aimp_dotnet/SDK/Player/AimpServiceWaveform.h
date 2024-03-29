//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace Player;

        public ref class AimpServiceWaveform :
            public BaseAimpService<IAIMPServiceWaveform>,
            public IAimpServiceWaveform {
        public:
            explicit AimpServiceWaveform(ManagedAimpCore^ core);

        protected:
            IAIMPServiceWaveform* GetAimpService() override;
        };
    }
}
