//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AIMPSDK/AIMP400/apiDecoders.h"
#include "SDK\BaseAimpService.h"

namespace AIMP {
    namespace SDK {
        using namespace MenuManager;

        public ref class AimpServiceMenuManager : public BaseAimpService<IAIMPServiceMenuManager>,
                                                  public IAimpServiceMenuManager {
        public:
            explicit AimpServiceMenuManager(ManagedAimpCore^ core);

            virtual ActionResult Add(IAimpMenuItem^ item);

            virtual ActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem^ item);

            virtual ActionResult Delete(IAimpMenuItem^ item);

            virtual ActionResult Delete(String^ id);

            virtual MenuItemResult GetById(String^ id);

            virtual MenuItemResult GetBuiltIn(ParentMenuType parentMenuType);

        private:
            HRESULT UnregisterMenu(IAIMPMenuItem* menuItem);
        protected:
            IAIMPServiceMenuManager* GetAimpService() override;
        };
    }
}
