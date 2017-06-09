// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpActionEvent.h"


AimpActionEvent::AimpActionEvent(gcroot<AIMP::SDK::ActionManager::IAimpActionEvent^> managedInstance, AIMP::SDK::AimpActionEventCallback cb)
{
    _cb = cb;
    _managedInstance = managedInstance;
}

void WINAPI AimpActionEvent::OnExecute(IUnknown *Data)
{
    _cb(_managedInstance, Data);
}

HRESULT WINAPI AimpActionEvent::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    if (riid == IID_IAIMPActionEvent)
    {
        *ppvObject = this;
        return S_OK;
    }

    ppvObject = NULL;
    return E_NOTIMPL;
}

ULONG WINAPI AimpActionEvent::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI AimpActionEvent::Release(void)
{
    return Base::Release();
}
