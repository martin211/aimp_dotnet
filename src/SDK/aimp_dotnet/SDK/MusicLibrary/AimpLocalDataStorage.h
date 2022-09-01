#pragma once
#include "DataStorage/AimpDataStorage2.h"

namespace AIMP {
    namespace SDK {

        public ref class AimpLocalDataStorage : public AimpDataStorage2, public IAimpLocalDataStorage {
        public:
            explicit AimpLocalDataStorage(IAIMPMLDataStorage2* obj);
        };
    }
}
