// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpMessageHook.h"

InternalAimpMessageHook::InternalAimpMessageHook(gcroot<IAimpMessageHook^> managedCore) {
    _managedCore = managedCore;
}

void InternalAimpMessageHook::CoreMessage(DWORD message, int param1, void* param2, HRESULT* result) {
    const auto res = _managedCore->CoreMessage(static_cast<AimpCoreMessageType>(message), param1, (int)param2);
    // do not set AResult here. It breaks a modal dialog
}

//HRESULT WINAPI InternalAimpMessageHook::QueryInterface(REFIID riid, LPVOID* ppvObject)
//{
//    HRESULT res = Base::QueryInterface(riid, ppvObject);
//
//    if (!ppvObject)
//    {
//        return E_POINTER;
//    }
//
//    if (riid == IID_IAIMPMessageHook)
//    {
//        *ppvObject = this;
//        AddRef();
//        return S_OK;
//    }
//
//    ppvObject = nullptr;
//    return res;
//}
//
//ULONG WINAPI InternalAimpMessageHook::AddRef(void)
//{
//    return Base::AddRef();
//}
//
//ULONG WINAPI InternalAimpMessageHook::Release(void)
//{
//    return Base::Release();
//}
