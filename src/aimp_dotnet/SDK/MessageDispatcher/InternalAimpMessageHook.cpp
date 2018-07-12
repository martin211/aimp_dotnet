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
#include "InternalAimpMessageHook.h"

InternalAimpMessageHook::InternalAimpMessageHook(gcroot<IAimpMessageHook^> managedCore)
{
    _managedCore = managedCore;
}

void InternalAimpMessageHook::CoreMessage(DWORD AMessage, int AParam1, void *AParam2, HRESULT *AResult)
{
    if (AMessage != (DWORD)AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_CMD_QUIT && AMessage != (DWORD)AIMP::SDK::AimpMessages::AimpCoreMessageType::AIMP_MSG_EVENT_TERMINATING)
    {
        AIMP::SDK::AimpActionResult res = _managedCore->CoreMessage((AIMP::SDK::AimpMessages::AimpCoreMessageType)AMessage, AParam1, (int)AParam2);
        *AResult = (HRESULT)res;
    }
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
//    ppvObject = NULL;
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
