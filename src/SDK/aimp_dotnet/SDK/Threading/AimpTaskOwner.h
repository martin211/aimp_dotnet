//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpSdk.h"

namespace AIMP {
    namespace SDK {
        using namespace SDK;
        using namespace Threading;

        public ref class AimpTaskOwner : public AimpObject<IAIMPTaskOwner>, public IAimpTaskOwner {
        public:
            explicit AimpTaskOwner(IAIMPTaskOwner* taskOwner);
        protected:
            void RegisterAtMemoryManager() override;
            void ReleaseFromMemoryManager() override;
        public:
            virtual property bool IsCanceled
            {
                bool get();
            }
        };
    }
}
