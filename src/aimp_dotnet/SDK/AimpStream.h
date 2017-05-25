// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once

namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK;

        public ref class AimpStream :
            public AimpObject<IAIMPStream>,
            public IAimpStream
        {
        public:
            explicit AimpStream(IAIMPStream *aimpObject);

            ~AimpStream();

            !AimpStream();

            // Inherited via IAimpStream
            virtual long long GetSize();

            virtual AIMP::SDK::AimpActionResult SetSize(long long value);

            virtual long long GetPosition();

            virtual AIMP::SDK::AimpActionResult Seek(long long offset, System::IO::SeekOrigin mode);

            virtual int Read(array<unsigned char, 1> ^buffer, int count);

            virtual AIMP::SDK::AimpActionResult Write(array<unsigned char, 1> ^buffer, int count, int %writen);
        };
    }
}
