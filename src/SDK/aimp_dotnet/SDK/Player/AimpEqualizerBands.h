//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace Player::Objects;

        public ref class AimpEqualizerBands :
            public AimpObject<IAIMPEqualizerBands>,
            public IAimpEqualizerBands {
        public:
            explicit AimpEqualizerBands(IAIMPEqualizerBands* obj);
            virtual int GetBandCount();
            virtual DoubleActionResult^ GetBandFrequency(int bandIndex);
            virtual DoubleActionResult^ GetBandGain(int bandIndex);
            virtual AimpActionResult^ SetBandGain(int index, double value);
        };
    }
}
