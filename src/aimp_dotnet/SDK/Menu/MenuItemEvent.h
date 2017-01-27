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