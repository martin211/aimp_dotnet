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

        public ref class AimpErrorInfo :
            public AimpObject<IAIMPErrorInfo>,
            public IAimpErrorInfo {
        public:
            explicit AimpErrorInfo(IAIMPErrorInfo* aimpObject);
            ~AimpErrorInfo();
            !AimpErrorInfo();
            virtual AimpActionResult<ErrorInfo^>^ GetInfo();
            virtual AimpActionResult<String^>^ GetInfoFormatted();
            virtual void SetInfo(int errorCode, String^ message, String^ details);
        };
    }
}
