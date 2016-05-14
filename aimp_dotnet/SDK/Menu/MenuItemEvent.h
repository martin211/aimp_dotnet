#pragma once
#include "..\..\IUnknownInterfaceImpl.h"
#include "AimpMenuManager.h"

namespace AIMP
{
    namespace SDK
    {
        #include "..\..\AIMPSDK\AIMP400\apiActions.h"

        class MenuItemEvent : public IUnknownInterfaceImpl<IAIMPActionEvent>
        {
        public:
            MenuItemEvent(gcroot<AIMP::SDK::MenuManager::IAimpMenuEvents^> menuItem, bool isExecuteEvent)
            {
                _menuItem = menuItem;
                _isExecuteEvent = isExecuteEvent;
            }

            virtual void WINAPI OnExecute(IUnknown *Data)
            {
                if (_isExecuteEvent)
                    _menuItem->Execute();
                else
                    _menuItem->Show();
            }

            virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject)
            {
                if (riid == IID_IAIMPActionEvent)
                {
                    *ppvObject = this;
                    return S_OK;
                }

                ppvObject = NULL;
                return E_NOTIMPL;
            }
        private:
            gcroot<AIMP::SDK::MenuManager::IAimpMenuEvents^> _menuItem;
            bool _isExecuteEvent;
        };
    }
}