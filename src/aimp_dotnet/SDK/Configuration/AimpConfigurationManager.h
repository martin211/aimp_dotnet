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
#include "SDK\AimpConfig.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace System;
        using namespace AIMP::SDK::ConfigurationManager;

        [System::Serializable]
        public ref class AimpServiceConfig :
            public AimpConfig,
            public IAimpServiceConfig
        {
        public:
            explicit AimpServiceConfig(IAIMPServiceConfig* aimpObject);

            ~AimpServiceConfig();

            virtual AimpActionResult FlushCache();
        };
    }
}
