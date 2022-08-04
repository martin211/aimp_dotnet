#pragma once
#include "AimpServiceFileURI.h"
#include "SDK/BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        public ref class AimpServiceFileURI2 :
            public AimpServiceFileURI,
            public IAimpServiceFileURI2 {
        public:
            explicit AimpServiceFileURI2(ManagedAimpCore^ core)
                : AimpServiceFileURI(core) {
            }

            virtual AimpActionResult<String^>^ GetScheme(String^ fileUri);
        };
    }
}
