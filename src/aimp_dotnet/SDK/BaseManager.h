/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#pragma once

#include "SDK\ManagedAimpCore.h"

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
