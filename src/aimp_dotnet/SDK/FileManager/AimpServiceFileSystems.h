/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once
#include "SDK\BaseManager.h"
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
