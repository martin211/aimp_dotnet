/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "MenuItemEvent.h"

AIMP::SDK::MenuItemEvent::MenuItemEvent(gcroot<AIMP::SDK::MenuManager::IAimpMenuEvents^> menuItem, bool isExecuteEvent)
{
    _menuItem = menuItem;
    _isExecuteEvent = isExecuteEvent;
}

void WINAPI AIMP::SDK::MenuItemEvent::OnExecute(IUnknown *Data)
{
    if (_isExecuteEvent)
        _menuItem->Execute();
    else
        _menuItem->Show();
}

HRESULT WINAPI AIMP::SDK::MenuItemEvent::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    if (riid == IID_IAIMPActionEvent)
    {
        *ppvObject = this;
        return S_OK;
    }

    ppvObject = NULL;
    return E_NOTIMPL;
}
