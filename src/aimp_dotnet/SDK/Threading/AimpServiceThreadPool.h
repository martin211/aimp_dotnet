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

            virtual ActionResultType Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);

            virtual ActionResultType Execute(IAimpTask^ task, UIntPtr% handle);

            virtual ActionResultType WaitFor(UIntPtr handle);
        protected:
            IAIMPServiceThreadPool* GetAimpService() override;
        };
    }
}
