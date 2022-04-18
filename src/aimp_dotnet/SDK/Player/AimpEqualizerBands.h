#pragma once

namespace AIMP {
    namespace SDK {
        using namespace Player::Primitives;

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
