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

#pragma once

using namespace System;
using namespace AIMP::SDK::MessageDispatcher;

class InternalAimpMessageHook : public IUnknownInterfaceImpl<IAIMPMessageHook>
{
public:
    typedef IUnknownInterfaceImpl<IAIMPMessageHook> Base;

    InternalAimpMessageHook(gcroot<IAimpMessageHook^> managedCore);
    virtual void WINAPI CoreMessage(DWORD AMessage, int AParam1, void *AParam2, HRESULT *AResult);

    //virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
    //virtual ULONG WINAPI AddRef(void);
    //virtual ULONG WINAPI Release(void);
private:
    gcroot<IAimpMessageHook^> _managedCore;
};