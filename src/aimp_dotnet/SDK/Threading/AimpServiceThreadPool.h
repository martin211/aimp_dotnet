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
#include "InternalAimpTask.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::Threading;

        public ref class AimpServiceThreadPool : public AimpBaseManager<IAIMPServiceThreadPool>, public IAimpServiceThreadPool
        {
        public:
            explicit AimpServiceThreadPool(ManagedAimpCore^ core);

            virtual AimpActionResult Cancel(UIntPtr taskHandle, AimpServiceThreadPoolType flags);

            virtual AimpActionResult Execute(IAimpTask ^task, UIntPtr %handle);

            virtual AimpActionResult WaitFor(UIntPtr handle);
        };
    }
}
