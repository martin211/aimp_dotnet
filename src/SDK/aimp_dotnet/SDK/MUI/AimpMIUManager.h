//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace MUIManager;

        public ref class AimpServiceMUI : public BaseAimpService<IAIMPServiceMUI>, public IAimpMUIManager
        {
        public:
            explicit AimpServiceMUI(ManagedAimpCore^ core);

            virtual String^ GetName();

            virtual String^ GetValue(String^ key);

            virtual String^ GetValuePart(String^ key, int index);
        };
    }
}
