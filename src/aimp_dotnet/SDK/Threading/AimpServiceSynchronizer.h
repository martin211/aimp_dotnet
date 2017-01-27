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
