//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpActionEvent.h"

using namespace AIMP::SDK;
using namespace Actions::Objects;

AimpActionEvent::AimpActionEvent(gcroot<IAimpActionEvent^> managedInstance, AimpActionEventCallback cb) {
    _cb = cb;
    _managedInstance = managedInstance;
}

AimpActionEvent::AimpActionEvent(gcroot<IAimpActionEvent^> managedInstance) {
    _managedInstance = managedInstance;
}

void WINAPI AimpActionEvent::OnExecute(IUnknown* Data) {
    if (_cb != nullptr) {
        _cb(_managedInstance, Data);
    }
    else {
        _managedInstance->OnExecute->Invoke(_managedInstance, nullptr);
    }
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
