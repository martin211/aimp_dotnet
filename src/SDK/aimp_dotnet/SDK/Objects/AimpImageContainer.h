// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once
#include "SDK/ManagedAimpCore.h"

namespace AIMP {
    namespace SDK {
        ref class AimpImageContainer :
            public AimpObject<IAIMPImageContainer>,
            public IAimpImageContainer {

        public:
            explicit AimpImageContainer(IAIMPImageContainer* container);

            virtual AimpActionResult<IAimpImage^>^ CreateImage();

            virtual AimpActionResult<Tuple<Size, int>^>^ GetInfo();

            virtual AimpActionResult<array<unsigned char>^>^ GetData();

            virtual unsigned GetDataSize();

            virtual AimpActionResult^ SetDataSize(long long value);
        };
    }
}
