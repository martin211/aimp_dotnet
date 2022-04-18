// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#pragma once

namespace AIMP {
    namespace SDK {
        public ref class AimpDPIAware :
            public AimpObject<IAIMPDPIAware>,
            public IAimpDPIAware {

        public:
            explicit AimpDPIAware(IAIMPDPIAware* obj);

            property int DPI {
                virtual int get();
                virtual void set(int dpi);
            }
        };
    }
}
