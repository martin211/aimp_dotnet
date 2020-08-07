// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpActionEvent.h"


using namespace AIMP::SDK;

AimpActionEvent::AimpActionEvent(gcroot<ActionManager::IAimpActionEvent^> managedInstance, AimpActionEventCallback cb) {
    _cb = cb;
    _managedInstance = managedInstance;
}

void WINAPI AimpActionEvent::OnExecute(IUnknown* Data) {
    _cb(_managedInstance, Data);
}

HRESULT WINAPI AimpActionEvent::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    if (riid == IID_IAIMPActionEvent) {
        *ppvObject = this;
        return S_OK;
    }

    *ppvObject = nullptr;
    return E_NOTIMPL;
}

ULONG WINAPI AimpActionEvent::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpActionEvent::Release(void) {
    return Base::Release();
}
