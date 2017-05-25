// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
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
        using namespace System::Windows::Input;
        using namespace AIMP::SDK;
        using namespace AIMP::SDK::ActionManager;

        public ref class AimpActionManager :
            public AimpBaseManager<IAIMPServiceActionManager>,
            public IAimpServiceActionManager
        {
        public:
            explicit AimpActionManager(ManagedAimpCore^ core);

            virtual AimpActionResult GetById(String ^id, IAimpAction ^%action);

            virtual int MakeHotkey(ModifierKeys modifiers, unsigned int key);

            virtual AimpActionResult Register(IAimpAction ^action);

            virtual AimpActionResult Register(System::Collections::Generic::ICollection<AIMP::SDK::ActionManager::IAimpAction^>^ actions);

            virtual IAimpAction ^CreateAction();
        };
    }
}
