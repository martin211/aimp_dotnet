//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#pragma once
#include "AimpSdk.h"
#include "AimpServiceSynchronizer.h"

class InternalAimpTask : public IUnknownInterfaceImpl<IAIMPTask> {
private:
    gcroot<IAimpTask^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPTask> Base;

    InternalAimpTask(gcroot<IAimpTask^> instance);

    virtual void WINAPI Execute(IAIMPTaskOwner* Owner);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
