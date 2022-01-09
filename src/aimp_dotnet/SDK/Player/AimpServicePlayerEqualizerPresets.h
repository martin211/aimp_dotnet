#pragma once
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        public ref class AimpServicePlayerEqualizerPresets :
            public BaseAimpService<IAIMPServicePlayerEqualizerPresets>,
            public Player::IAimpServicePlayerEqualizerPresets {
        public:
            explicit AimpServicePlayerEqualizerPresets(ManagedAimpCore^ core)
                : BaseAimpService<IAIMPServicePlayerEqualizerPresets>(core) {
            }
            virtual AimpActionResult<Player::IAimpEqualizerPreset^>^ Add(String^ name);
            virtual AimpActionResult<Player::IAimpEqualizerPreset^>^ FindByName(String^ name);
            virtual AimpActionResult^ Delete(Player::IAimpEqualizerPreset^ preset);
            virtual AimpActionResult^ Delete(int index);
            virtual AimpActionResult<Player::IAimpEqualizerPreset^>^ GetPreset(int index);
            virtual int GetPresetCount();
        protected:
            IAIMPServicePlayerEqualizerPresets* GetAimpService() override;
        };
    }
}
