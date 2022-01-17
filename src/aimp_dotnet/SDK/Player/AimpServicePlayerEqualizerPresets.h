#pragma once
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace  Player::Primitives;
        using namespace  Player::Services;

        public ref class AimpServicePlayerEqualizerPresets :
            public BaseAimpService<IAIMPServicePlayerEqualizerPresets>,
            public IAimpServicePlayerEqualizerPresets {
        public:
            explicit AimpServicePlayerEqualizerPresets(ManagedAimpCore^ core)
                : BaseAimpService<IAIMPServicePlayerEqualizerPresets>(core) {
            }
            virtual AimpActionResult<IAimpEqualizerPreset^>^ Add(String^ name);
            virtual AimpActionResult<IAimpEqualizerPreset^>^ FindByName(String^ name);
            virtual AimpActionResult^ Delete(IAimpEqualizerPreset^ preset);
            virtual AimpActionResult^ Delete(int index);
            virtual AimpActionResult<IAimpEqualizerPreset^>^ GetPreset(int index);
            virtual int GetPresetCount();
        protected:
            IAIMPServicePlayerEqualizerPresets* GetAimpService() override;
        };
    }
}
