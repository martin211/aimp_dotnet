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

#include "..\BaseManager.h"
#include "ICallBackHeader.h"
#include "AimpMenuItem.h"


namespace AIMP
{
    namespace SDK
    {
        using namespace AIMP::SDK::MenuManager;

        public ref class AimpMenuManager : public AimpBaseManager<IAIMPServiceMenuManager>, public IAimpMenuManager
        {
        public:
            explicit AimpMenuManager(ManagedAimpCore^ core);

            virtual AimpActionResult CreateMenuItem(IAimpMenuItem ^%item);

            ~AimpMenuManager();

            virtual AimpActionResult Add(IAimpMenuItem ^item);

            virtual AimpActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem ^item);

            virtual AimpActionResult Delete(IAimpMenuItem ^item);

            virtual AimpActionResult Delete(String ^id);

            virtual AimpActionResult GetById(String ^id, IAimpMenuItem ^%item);

            virtual AimpActionResult GetBuiltIn(ParentMenuType parentMenuType, IAimpMenuItem ^%item);

        private:
            HRESULT UnregisterMenu(IAIMPMenuItem* menuItem);
        };
    }
}
