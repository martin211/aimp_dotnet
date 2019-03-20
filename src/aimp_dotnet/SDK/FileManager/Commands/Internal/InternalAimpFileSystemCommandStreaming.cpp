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
#include "InternalAimpFileSystemCommandStreaming.h"

using namespace AIMP::SDK;

InternalAimpFileSystemCommandStreaming::InternalAimpFileSystemCommandStreaming(gcroot<Commands::IAimpFileSystemCommandStreaming^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandStreaming::CreateStream(IAIMPString* fileName, const INT64 offset, const INT64 size, DWORD flags, IAIMPStream** stream)
{
    IAimpStream^ aimpStream = _instance->CreateStream(AimpConverter::ToManagedString(fileName), FileStreamingType(flags), offset, size);
    if (aimpStream != nullptr)
    {
        *stream = static_cast<AimpStream^>(aimpStream)->InternalAimpObject;
        return S_OK;
    }

    *stream = nullptr;
    return E_FAIL;
}

ULONG WINAPI InternalAimpFileSystemCommandStreaming::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandStreaming::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandStreaming::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandStreaming)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
