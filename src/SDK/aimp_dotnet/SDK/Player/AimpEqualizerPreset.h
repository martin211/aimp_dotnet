//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpEqualizerBands.h"

namespace AIMP {
    namespace SDK {
        using namespace Player::Objects;

        public ref class AimpEqualizerPreset :
            public AimpEqualizerBands,
            public IAimpEqualizerPreset
        {
        public:
            explicit AimpEqualizerPreset(IAIMPEqualizerPreset* obj);
            virtual StringActionResult^ GetName();
            virtual AimpActionResult^ SetName(IAimpString^ value);
        };
    }
}
