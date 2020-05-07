// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace Windows::Input;
        using namespace SDK;
        using namespace ActionManager;

        [System::Serializable]
        public ref class AimpServiceActionManager :
            public BaseAimpService<IAIMPServiceActionManager>,
            public IAimpServiceActionManager
        {
        public:
            explicit AimpServiceActionManager(ManagedAimpCore^ core);

            virtual ActionResultType GetById(String^ id, IAimpAction^% action);

            virtual int MakeHotkey(ModifierKeys modifiers, unsigned int key);

            virtual ActionResultType Register(IAimpAction^ action);

            virtual ActionResultType Register(Generic::ICollection<IAimpAction^>^ actions);

            virtual IAimpAction^ CreateAction();

        protected:
            IAIMPServiceActionManager* GetAimpService() override;
        };
    }
}
