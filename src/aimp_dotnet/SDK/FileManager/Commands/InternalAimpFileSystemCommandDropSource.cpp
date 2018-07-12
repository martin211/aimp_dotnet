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
#include "InternalAimpFileSystemCommandDropSource.h"
#include "../../../SDK/AimpString.h"
#include "../../../SDK/AimpStream.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandDropSource::InternalAimpFileSystemCommandDropSource(gcroot<IAimpFileSystemCommandDropSource^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandDropSource::CreateStream(IAIMPString* FileName, IAIMPStream** Stream)
{
    IAimpStream^ stream = _instance->CreateStream(gcnew AimpString(FileName));
    if (stream != nullptr)
    {
        *Stream = ((AimpStream^)stream)->InternalAimpObject;
        return S_OK;
    }
    return (HRESULT)S_OK;
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

    *ppvObject = NULL;
    return res;
}
