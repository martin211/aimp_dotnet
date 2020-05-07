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
        using namespace Threading;

        public ref class AimpServiceSynchronizer :
            public BaseAimpService<IAIMPServiceSynchronizer>,
            public IAimpServiceSynchronizer
        {
        public:
            explicit AimpServiceSynchronizer(ManagedAimpCore^ core);

            virtual ActionResultType ExecuteInMainThread(IAimpTask^ task, bool executeNow);
        protected:
            IAIMPServiceSynchronizer* GetAimpService() override;
        };
    }
}
