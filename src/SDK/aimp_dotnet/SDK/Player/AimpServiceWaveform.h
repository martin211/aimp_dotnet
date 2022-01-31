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
