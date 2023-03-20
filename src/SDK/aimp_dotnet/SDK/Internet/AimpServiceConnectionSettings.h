//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once

#include "SDK/BaseAimpService.h"
#include "AIMPSDK/AIMP400/apiInternet.h"

namespace AIMP {
    namespace SDK {
        using namespace Internet;

        public ref class AimpServiceConnectionSettings :
            public BaseAimpService<IAIMPServiceConnectionSettings>,
            public IAimpServiceConnectionSettings {
        public:
            explicit AimpServiceConnectionSettings(ManagedAimpCore^ core);

            ~AimpServiceConnectionSettings();

            virtual property ConnectionType ConnectionType {
                Internet::ConnectionType get();
                void set(Internet::ConnectionType value);
            }

            virtual property String^ ProxyServer {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ ProxyPort {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ ProxyUserName {
                String^ get();
                void set(String^ value);
            }

            virtual property String^ ProxyUserPass {
                String^ get();
                void set(String^ value);
            }

            virtual property int TimeOut {
                int get();
                void set(int value);
            }

            virtual property String^ UserAgent {
                String^ get();
                void set(String^ value);
            }
        protected:
            IAIMPServiceConnectionSettings* GetAimpService() override;
        };
    }
}
