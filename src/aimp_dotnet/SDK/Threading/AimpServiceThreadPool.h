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
#include "InternalAimpTask.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Threading;

        [System::Serializable]
        public ref class AimpServiceThreadPool : public AimpBaseManager<IAIMPServiceThreadPool>, public IAimpServiceThreadPool
        {
        public:
            explicit AimpServiceThreadPool(ManagedAimpCore^ core);

            virtual AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);

            virtual AimpActionResult Execute(IAimpTask ^task, UIntPtr %handle);

            virtual AimpActionResult WaitFor(UIntPtr handle);
        };
    }
}
