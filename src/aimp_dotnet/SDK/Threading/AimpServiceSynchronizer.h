/* AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 */
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
