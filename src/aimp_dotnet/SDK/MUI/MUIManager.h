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
        using namespace System;
        using namespace AIMP::SDK::MUIManager;

        [System::Serializable]
        public ref class AimpMIUManager : public AimpBaseManager<IAIMPServiceMUI>, public IAimpMUIManager
        {
        public:
            explicit AimpMIUManager(ManagedAimpCore^ core);

            ~AimpMIUManager();

            virtual String^ GetName();

            virtual String^ GetValue(String^ key);

            virtual String^ GetValuePart(String^ key, int index);
        };
    }
}
