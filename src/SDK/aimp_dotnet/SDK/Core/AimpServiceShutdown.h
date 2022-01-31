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
        namespace Core {
            public ref class AimpServiceShutdown :
                public BaseAimpService<IAIMPServiceShutdown>,
                public IAimpServiceShutdown {

            public:
                explicit AimpServiceShutdown(ManagedAimpCore^ core);
                virtual AimpActionResult^ Restart(String^ arguments);
                virtual AimpActionResult^ Shutdown(ShutdownType shutdownType);
            protected:
                IAIMPServiceShutdown* GetAimpService() override;
            };
        }
    }
}
