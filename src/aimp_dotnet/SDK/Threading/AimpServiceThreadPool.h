// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP {
    namespace SDK {
        using namespace Threading;

        public ref class AimpServiceThreadPool : public BaseAimpService<IAIMPServiceThreadPool>,
                                                 public IAimpServiceThreadPool {
        public:
            explicit AimpServiceThreadPool(ManagedAimpCore^ core);

            virtual ActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);

            virtual AimpActionResult<UIntPtr>^ Execute(IAimpTask^ task);

            virtual ActionResult WaitFor(UIntPtr handle);
        protected:
            IAIMPServiceThreadPool* GetAimpService() override;
        };
    }
}
