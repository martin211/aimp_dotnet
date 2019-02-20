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
#include "InternalAimpFileSystemCommandDelete.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandDelete::InternalAimpFileSystemCommandDelete(gcroot<IAimpFileSystemCommandDelete^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandDelete::CanProcess(IAIMPString* FileName)
{
    return (HRESULT)_instance->CanProcess(AimpConverter::ToManagedString(FileName));
}

HRESULT WINAPI InternalAimpFileSystemCommandDelete::Process(IAIMPString* FileName)
{
    return (HRESULT)_instance->Process(AimpConverter::ToManagedString(FileName));
}

ULONG WINAPI InternalAimpFileSystemCommandDelete::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandDelete::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandDelete::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandDelete)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
