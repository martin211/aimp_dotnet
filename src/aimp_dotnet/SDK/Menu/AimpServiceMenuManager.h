// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#pragma once
#include "SDK\BaseManager.h"

namespace AIMP
{
    namespace SDK
    {
        using namespace MenuManager;

        public ref class AimpServiceMenuManager : public BaseAimpService<IAIMPServiceMenuManager>,
                                           public IAimpServiceMenuManager
        {
        public:
            explicit AimpServiceMenuManager(ManagedAimpCore^ core);

            virtual ActionResultType CreateMenuItem(IAimpMenuItem^% item);

            virtual ActionResultType Add(IAimpMenuItem^ item);

            virtual ActionResultType Add(ParentMenuType parentMenuType, IAimpMenuItem^ item);

            virtual ActionResultType Delete(IAimpMenuItem^ item);

            virtual ActionResultType Delete(String^ id);

            virtual ActionResultType GetById(String^ id, IAimpMenuItem^% item);

            virtual ActionResultType GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem^% item);

        private:
            HRESULT UnregisterMenu(IAIMPMenuItem* menuItem);
        protected:
            IAIMPServiceMenuManager* GetAimpService() override;
        };
    }
}
