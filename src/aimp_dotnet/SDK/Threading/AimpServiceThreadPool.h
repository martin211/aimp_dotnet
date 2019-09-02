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

        public ref class AimpServiceThreadPool : public BaseAimpService<IAIMPServiceThreadPool>,
                                                 public IAimpServiceThreadPool
        {
        public:
            explicit AimpServiceThreadPool(ManagedAimpCore^ core);

            virtual AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);

            virtual AimpActionResult Execute(IAimpTask^ task, UIntPtr% handle);

            virtual AimpActionResult WaitFor(UIntPtr handle);
        protected:
            IAIMPServiceThreadPool* GetAimpService() override;
        };
    }
}
