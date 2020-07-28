// ----------------------------------------------------
// AIMP DotNet SDK
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// Mail: mail4evgeniy@gmail.com
// ----------------------------------------------------

#include "Stdafx.h"
#include "AimpDataStorageCommandAddFiles.h"

AimpDataStorageCommandAddFiles::AimpDataStorageCommandAddFiles(gcroot<MusicLibrary::Extension::Command::IAimpDataStorageCommandAddFiles^> instance) {
    _instance = instance;
}

HRESULT AimpDataStorageCommandAddFiles::Add(IAIMPObjectList* Files) {
    return HRESULT(_instance->Add(nullptr)->ResultType);
}

HRESULT AimpDataStorageCommandAddFiles::QueryInterface(const IID& riid, LPVOID* ppvObject) {
    *ppvObject = nullptr;
    if (riid == IID_IAIMPMLDataStorageCommandAddFiles)
    {
        *ppvObject = this;
        AddRef();
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG AimpDataStorageCommandAddFiles::AddRef() {
    return Base::AddRef();
}

ULONG AimpDataStorageCommandAddFiles::Release() {
    return Base::Release();
}
