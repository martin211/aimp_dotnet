#pragma once
#include "InternalAimpTask.h"
#include "..\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Threading;

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