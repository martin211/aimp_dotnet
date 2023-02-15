//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandUserMark.h"

AimpDataStorageCommandUserMark::AimpDataStorageCommandUserMark(
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandUserMark^> instance) {
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandUserMark::SetMark(VARIANT* ID, const DOUBLE Value) {
    return HRESULT(_instance->SetMark(AimpConverter::FromVariant(ID), Value)->ResultType);
}

HRESULT WINAPI AimpDataStorageCommandUserMark::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandUserMark) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandUserMark::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandUserMark::Release(void) {
    return Base::Release();
}
