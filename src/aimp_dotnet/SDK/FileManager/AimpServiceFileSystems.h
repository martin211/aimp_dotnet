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
			where TCommand : gcnew()
            virtual AimpActionResult Get(String ^fileUri, TCommand %command);

            generic<typename TCommand>
			where TCommand : gcnew()
            virtual AimpActionResult GetDefault(TCommand %command);
        };
    }
}
