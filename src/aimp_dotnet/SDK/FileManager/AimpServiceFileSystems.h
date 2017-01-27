/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
