//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandDropData.h"

AimpDataStorageCommandDropData::AimpDataStorageCommandDropData(
    gcroot<AIMP::SDK::MusicLibrary::Extension::Command::IAimpDataStorageCommandDropData^> instance) {
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandDropData::DropData() {
    return HRESULT(_instance->DropData()->ResultType);
}

HRESULT WINAPI AimpDataStorageCommandDropData::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandDropData) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandDropData::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandDropData::Release(void) {
    return Base::Release();
}
