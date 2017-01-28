#pragma once
#include "..\BaseManager.h"
#include "Commands\InternalAimpFileSystemCommandFileInfo.h"
#include "Commands\AimpFileSystemCommandFileInfo.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::FileManager;
        using namespace AIMP::SDK::FileManager::Commands;

        public ref class AimpServiceFileSystems : public AimpBaseManager<IAIMPServiceFileSystems>, public IAimpServiceFileSystems
        {
        public:
            AimpServiceFileSystems(ManagedAimpCore^ core);

            generic<typename TCommand>
            virtual AimpActionResult Get(String ^fileUri, IAimpFileSystemCommand ^%command);

            generic<typename TCommand>
            virtual AimpActionResult GetDefault(IAimpFileSystemCommand ^%command);
        };
    }
}