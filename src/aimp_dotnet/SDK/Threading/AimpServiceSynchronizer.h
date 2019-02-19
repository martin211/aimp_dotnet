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
        using namespace Threading;

        public ref class AimpServiceSynchronizer :
            public AimpBaseManager<IAIMPServiceSynchronizer>,
            public IAimpServiceSynchronizer
        {
        public:
            explicit AimpServiceSynchronizer(ManagedAimpCore^ core);

            virtual AimpActionResult ExecuteInMainThread(IAimpTask^ task, bool executeNow);
        };
    }
}
