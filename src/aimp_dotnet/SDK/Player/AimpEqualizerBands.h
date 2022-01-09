#pragma once

namespace AIMP {
    namespace SDK {
        public ref class AimpEqualizerBands :
            public AimpObject<IAIMPEqualizerBands>,
            public Player::IAimpEqualizerBands {
        public:
            explicit AimpEqualizerBands(IAIMPEqualizerBands* obj);
            virtual int GetBandCount();
            virtual DoubleActionResult^ GetBandFrequency(int bandIndex);
            virtual DoubleActionResult^ GetBandGain(int bandIndex);
            virtual AimpActionResult^ SetBandGain(int index, double value);
        };
    }
}
