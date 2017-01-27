/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
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
