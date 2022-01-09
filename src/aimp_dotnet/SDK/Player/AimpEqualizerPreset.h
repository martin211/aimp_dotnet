#pragma once
#include "AimpEqualizerBands.h"

namespace AIMP {
    namespace SDK {
        public ref class AimpEqualizerPreset :
            public AimpEqualizerBands,
            public Player::IAimpEqualizerPreset
        {
        public:
            explicit AimpEqualizerPreset(IAIMPEqualizerPreset* obj);
            virtual StringActionResult^ GetName();
            virtual AimpActionResult^ SetName(IAimpString^ value);
        };
    }
}
