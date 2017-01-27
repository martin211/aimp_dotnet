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

#include "..\ManagedAimpCore.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;

        template<typename TAimpService>
        public ref class AimpBaseManager abstract
        {
        public:
            AimpBaseManager(ManagedAimpCore^ core)
            {
                _core = core;
            }
        protected:
            AimpActionResult CheckResult(HRESULT result)
            {
                AimpActionResult res = Utils::CheckResult(result);
                if (res != AimpActionResult::Ok)
                {
                    //AIMP::SDK::InternalLogger::Instance->Write("Invalid operation: result " + result);
                }

                return res;
            }

            AimpActionResult GetService(const IID id, TAimpService **service)
            {
                TAimpService *s;
                AimpActionResult result = CheckResult(_core->GetService(id, (void**)&s));

                if (result == AimpActionResult::Ok)
                {
                    *service = s;
                }

                return result;
            }

            ManagedAimpCore^ _core;
        };
    }
}
