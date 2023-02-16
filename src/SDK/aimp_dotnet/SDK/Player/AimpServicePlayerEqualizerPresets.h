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
        using namespace  Player::Objects;
        using namespace  Player;

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
