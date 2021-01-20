// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace Threading;

        public ref class AimpServiceThreads : public BaseAimpService<IAIMPServiceThreads>,
                                              public IAimpServiceThreads {
        public:
            explicit AimpServiceThreads(ManagedAimpCore^ core);
            virtual AimpActionResult^ Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);
            virtual AimpActionResult^ WaitFor(UIntPtr taskHandle);
            virtual AimpActionResult^ ExecuteInMainThread(IAimpTask^ task, bool executeNow);
            virtual AimpActionResult<UIntPtr>^ ExecuteInThread(IAimpTask^ task);
        protected:
            IAIMPServiceThreads* GetAimpService() override;
        };
    }
}

