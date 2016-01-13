#pragma once

#include "..\ManagedAimpCore.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;

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

            AimpActionResult GetService(GUID id, IUnknown **service)
            {
                IUnknown *s;
                AimpActionResult result = CheckResult(_core->GetService(IID_IAIMPServiceActionManager, (void**)&s));

                if (result == AimpActionResult::Ok)
                {
                    *service = s;
                }

                return result;
            }

            ManagedAimpCore^ _core;
        };

        template<typename T>
        public ref class AimpBaseManager2 abstract
        {
        public:
            AimpBaseManager2(ManagedAimpCore^ core)
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

            AimpActionResult GetService(GUID id, T **service)
            {
                T *s;
                AimpActionResult result = CheckResult(_core->GetService(IID_IAIMPServiceActionManager, (void**)&s));

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