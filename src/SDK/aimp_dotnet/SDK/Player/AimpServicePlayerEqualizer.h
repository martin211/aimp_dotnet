//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "SDK\BaseAimpService.h"
#include "AimpEqualizerBands.h"

namespace AIMP {
    namespace SDK {
        using namespace Player;
        using namespace Player::Objects;

    public ref class AimpServicePlayerEqualizer :
        public AimpEqualizerBands,
        public IAimpBaseService<IAIMPServicePlayerEqualizer>,
        public IAimpServicePlayerEqualizer {
    public:
        AimpServicePlayerEqualizer(ManagedAimpCore^ core) : AimpEqualizerBands(nullptr), _core(core) {
        }

        virtual bool GetActive();
        virtual ActionResult SetActive(bool value);
        virtual DoubleResult GetPreamp();
        virtual ActionResult SetPreamp(double value);
        virtual AimpActionResult<IAimpEqualizerPreset^>^ GetPreset();
        virtual ActionResult SetPreset(IAimpEqualizerPreset^ value);
        property bool IsExists { virtual bool get(); }
        virtual IAIMPServicePlayerEqualizer* QueryInterface();
        private:
            ManagedAimpCore^ _core;
            void ReleaseObject(IUnknown* object);
        };
    }
}
