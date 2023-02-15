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
        public ref class AimpMemoryStream :
            public AimpStream,
            public IAimpMemoryStream {
        public:
            AimpMemoryStream(IAIMPMemoryStream* aimpObject);
            virtual AimpActionResult<array<unsigned char>^>^ GetData();
        };
    }
}
