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
#include "InternalAimpTask.h"

InternalAimpTask::InternalAimpTask(gcroot<AIMP::SDK::Threading::IAimpTask^> instance)
{
    _instance = instance;
}

void WINAPI InternalAimpTask::Execute(IAIMPTaskOwner* Owner)
{
    AimpTaskOwner ^owner = gcnew AimpTaskOwner(Owner);
    _instance->Execute(owner);
}

ULONG WINAPI InternalAimpTask::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpTask::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpTask::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPTask)
    {
        *ppvObject = this;
        return S_OK;
    }

    ppvObject = NULL;
    return res;
}
