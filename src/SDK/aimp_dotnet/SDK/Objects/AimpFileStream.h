//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        public ref class AimpFileStream :
            public AimpStream,
            public IAimpFileStream {
        public:
            explicit AimpFileStream(IAIMPFileStream* aimpObject);
            virtual AimpActionResult<Clipping^>^ GetClipping();
            virtual AimpActionResult<IAimpString^>^ GetFileName();
        };
    }
}
