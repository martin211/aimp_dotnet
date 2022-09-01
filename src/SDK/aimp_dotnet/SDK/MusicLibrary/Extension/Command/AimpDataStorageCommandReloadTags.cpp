//  ----------------------------------------------------
//  AIMP DotNet SDK
//  
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
//  
//  Mail: mail4evgeniy@gmail.com 
//  ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandReloadTags.h"

#include "SDK/MusicLibrary/AimpFileList.h"

AimpDataStorageCommandReloadTags::AimpDataStorageCommandReloadTags(
    gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandReloadTags^> instance) {
    _instance = instance;
}

HRESULT WINAPI AimpDataStorageCommandReloadTags::ReloadTags(IAIMPMLFileList* Files) {
    return HRESULT(_instance->ReloadTags(gcnew AimpFileList(Files))->ResultType);
}

HRESULT WINAPI AimpDataStorageCommandReloadTags::QueryInterface(REFIID riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandReloadTags) {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG WINAPI AimpDataStorageCommandReloadTags::AddRef(void) {
    return Base::AddRef();
}

ULONG WINAPI AimpDataStorageCommandReloadTags::Release(void) {
    return Base::Release();
}
