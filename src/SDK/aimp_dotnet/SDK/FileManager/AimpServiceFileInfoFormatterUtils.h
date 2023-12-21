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

namespace AIMP {
    namespace SDK {
        using namespace Windows;
        using namespace Actions::Objects;

        public ref class AimpServiceFileInfoFormatterUtils : public BaseAimpService<IAIMPServiceFileInfoFormatterUtils>,
                                                             public IAimpServiceFileInfoFormatterUtils {
        public:
            explicit AimpServiceFileInfoFormatterUtils(ManagedAimpCore^ core);
            virtual AimpActionResult^ ShowMacrosLegend(RectangleF screenTarget, IAimpActionEvent^ actionEvent);
        protected:
            IAIMPServiceFileInfoFormatterUtils* GetAimpService() override;
        };
    }
}
