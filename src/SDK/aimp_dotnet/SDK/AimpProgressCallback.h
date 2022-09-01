//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        using namespace AIMP::SDK;

        public ref class AimpProgressCallback :
            public AimpObject<IAIMPProgressCallback>,
            public IAimpProgressCallback {
        public:
            explicit AimpProgressCallback(IAIMPProgressCallback* aimpObject);
            virtual AimpActionResult^ Process(double progress, bool canceled);
        };
    }
}
