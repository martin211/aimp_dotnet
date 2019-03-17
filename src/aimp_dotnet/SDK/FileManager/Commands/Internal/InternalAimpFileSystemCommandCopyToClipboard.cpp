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

/*
 * AIMP DotNet SDK
 * 
 * (C) 2017
 * Mail: mail4evgeniy@gmail.com
 * https://github.com/martin211/aimp_dotnet
 * 
 */
#include "Stdafx.h"
#include "InternalAimpFileSystemCommandCopyToClipboard.h"


InternalAimpFileSystemCommandCopyToClipboard::InternalAimpFileSystemCommandCopyToClipboard(gcroot<IAimpFileSystemCommandCopyToClipboard^> instance)
{
    _instance = instance;
}

HRESULT WINAPI InternalAimpFileSystemCommandCopyToClipboard::CopyToClipboard(IAIMPObjectList* Files)
{
    return static_cast<HRESULT>(_instance->CopyToClipboard(AIMP::SDK::AimpConverter::ToStringCollection(Files)));
}

ULONG WINAPI InternalAimpFileSystemCommandCopyToClipboard::AddRef(void)
{
    return Base::AddRef();
}

ULONG WINAPI InternalAimpFileSystemCommandCopyToClipboard::Release(void)
{
    return Base::Release();
}

HRESULT WINAPI InternalAimpFileSystemCommandCopyToClipboard::QueryInterface(REFIID riid, LPVOID* ppvObject)
{
    HRESULT res = Base::QueryInterface(riid, ppvObject);

    if (riid == IID_IAIMPFileSystemCommandCopyToClipboard)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    *ppvObject = nullptr;
    return res;
}
