// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

#include "Stdafx.h"
#include "InternalAimpFileSystemCommandDropSource.h"
#include "SDK/AimpString.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandDropSource::InternalAimpFileSystemCommandDropSource(
    gcroot<IAimpFileSystemCommandDropSource^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandDropSource::CreateStream(IAIMPString* fileName, IAIMPStream** stream)
{
    const auto res = _instance->CreateStream(AimpConverter::ToManagedString(fileName));
    if (stream != nullptr)
    {
        *stream = static_cast<AimpStream^>(res->Result)->InternalAimpObject;
    }

    return HRESULT(res->ResultType);
}

ULONG WINAPI InternalAimpFileSystemCommandDropSource::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandDropSource::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandDropSource::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandDropSource)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
