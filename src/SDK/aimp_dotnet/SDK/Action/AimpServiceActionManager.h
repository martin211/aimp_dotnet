// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace Windows::Input;
        using namespace SDK;
        using namespace Actions;
        using namespace Actions::Objects;

        [System::Serializable]
        public ref class AimpServiceActionManager :
            public BaseAimpService<IAIMPServiceActionManager>,
            public IAimpServiceActionManager {
        public:
            explicit AimpServiceActionManager(ManagedAimpCore^ core);

            virtual AimpActionResult<IAimpAction^>^ GetById(String^ id);

            virtual int MakeHotkey(ModifierKeys modifiers, unsigned int key);

            virtual AimpActionResult^ Register(IAimpAction^ action);

            virtual AimpActionResult^ Register(Generic::ICollection<IAimpAction^>^ actions);

            virtual IAimpAction^ CreateAction();

        protected:
            IAIMPServiceActionManager* GetAimpService() override;
        };
    }
}
