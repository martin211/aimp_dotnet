// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

#include "SDK\ManagedAimpCore.h"

namespace AIMP {
    namespace SDK {
        using namespace AIMP::SDK;

        template <typename TAimpService>
        [System::Serializable]
        public ref class BaseAimpService abstract : IAimpService {
        private:
            bool _isExist;
            bool _initialized;
        public:
            BaseAimpService(ManagedAimpCore^ core) {
                _core = core;
                _isExist = false;
                _initialized = false;
            }

        protected:
            ActionResultType CheckResult(HRESULT result) {
                const ActionResultType res = Utils::CheckResult(result);
                if (res != ActionResultType::OK) {
                    //AIMP::SDK::InternalLogger::Instance->Write("Invalid operation: result " + result);
                }

                return res;
            }

            AimpActionResult^ GetResult(HRESULT result) {
                return gcnew AimpActionResult(CheckResult(result));
            }

            AimpActionResult^ GetResult(ActionResultType result) {
                return gcnew AimpActionResult(result);
            }

            ActionResultType GetService(const IID id, TAimpService** service) {
                TAimpService* s = nullptr;
                const ActionResultType result = CheckResult(_core->GetService(id, reinterpret_cast<void**>(&s)));

                if (result == ActionResultType::OK && s != nullptr) {
                    *service = s;
                    _isExist = true;
                }

                return result;
            }

            void ReleaseObject(IUnknown* object) {
                if (object != nullptr) {
                    object->Release();
                    object = nullptr;
                }
            }

            virtual TAimpService* GetAimpService() = 0;

        public:
            property bool IsExists
            {
                virtual bool get() {
                    if (!_initialized) {
                        _isExist = GetAimpService() != nullptr;
                        _initialized = true;
                    }
                    return _isExist;
                }
            }
        protected:
            ManagedAimpCore^ _core;
        };
    }
}
