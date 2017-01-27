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
#include "..\..\IUnknownInterfaceImpl.h"
#include "AimpMenuManager.h"

namespace AIMP
{
    namespace SDK
    {
        class MenuItemEvent : public IUnknownInterfaceImpl<IAIMPActionEvent>
        {
        public:
            MenuItemEvent(gcroot<AIMP::SDK::MenuManager::IAimpMenuEvents^> menuItem, bool isExecuteEvent);

            virtual void WINAPI OnExecute(IUnknown *Data);

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
        private:
            gcroot<AIMP::SDK::MenuManager::IAimpMenuEvents^> _menuItem;
            bool _isExecuteEvent;
        };
    }
}
