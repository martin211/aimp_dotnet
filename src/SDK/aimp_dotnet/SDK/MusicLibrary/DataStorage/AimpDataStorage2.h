#pragma once

#include "BaseAimpDataStorage.h"
#include "SDK/MusicLibrary/DataFilter/AimpDataFilter.h"

namespace AIMP {
    namespace SDK {

        using namespace System;
        using namespace DataStorage;
        using namespace Presets;


        public ref class AimpDataStorage2 : public BaseAimpDataStorage<IAIMPMLDataStorage2>, public IAimpDataStorage2 {
        public:
            explicit AimpDataStorage2(IAIMPMLDataStorage2* obj) : BaseAimpDataStorage<IAIMPMLDataStorage2>(obj) {
            }

            virtual AimpActionResult<Object^>^ CreateObject() {
                IAIMPMLDataFilter* obj = nullptr;

                const auto res = CheckResult(InternalAimpObject->CreateObject(IID_IAIMPMLDataFilter, reinterpret_cast<void**>(&obj)));
                if (res == ActionResultType::OK && obj != nullptr) {
                    return gcnew AimpActionResult<Object^>(res, gcnew AimpDataFilter(obj));
                }

                return gcnew AimpActionResult<Object^>(res);
            }
        };
    }
}


