/*
 * AIMP DotNet SDK
 *
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 */
 
#pragma once
#include "..\..\AimpSdk.h"
#include "AimpServiceSynchronizer.h"
#include "AimpTaskOwner.h"

class InternalAimpTask : public IUnknownInterfaceImpl<IAIMPTask>
{
private:
    gcroot<AIMP::SDK::Threading::IAimpTask^> _instance;
public:
    typedef IUnknownInterfaceImpl<IAIMPTask> Base;

    InternalAimpTask(gcroot<AIMP::SDK::Threading::IAimpTask^> instance);

    virtual void WINAPI Execute(IAIMPTaskOwner* Owner);

    virtual ULONG WINAPI AddRef(void);

    virtual ULONG WINAPI Release(void);

    virtual HRESULT WINAPI QueryInterface(REFIID riid, LPVOID* ppvObject);
};
