#pragma once
#include "AimpEqualizerBands.h"

namespace AIMP {
    namespace SDK {
        using namespace Player::Primitives;

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
