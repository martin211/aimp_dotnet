#pragma once
#include "SDK\BaseAimpService.h"
#include "AimpEqualizerBands.h"

namespace AIMP {
    namespace SDK {
        public ref class AimpServicePlayerEqualizer :
        public AimpEqualizerBands,
        public IAimpBaseService<IAIMPServicePlayerEqualizer>,
        public Player::IAimpServicePlayerEqualizer {
    public:
        AimpServicePlayerEqualizer(ManagedAimpCore^ core) : AimpEqualizerBands(nullptr), _core(core) {
        }

        virtual bool GetActive();
        virtual ActionResult SetActive(bool value);
        virtual DoubleResult GetPreamp();
        virtual ActionResult SetPreamp(double value);
        virtual AimpActionResult<Player::IAimpEqualizerPreset^>^ GetPreset();
        virtual ActionResult SetPreset(Player::IAimpEqualizerPreset^ value);
        property bool IsExists { virtual bool get(); }
        virtual IAIMPServicePlayerEqualizer* QueryInterface();
        private:
            ManagedAimpCore^ _core;
            void ReleaseObject(IUnknown* object);
        };
    }
}
